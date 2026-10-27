// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once
#include "assets/GameFont.hpp"
#include "render/MessageListDrawing.hpp"
#include "render/SurfaceFill.hpp"
#include "sim/MessageExpiry.hpp"
#include <memory>
namespace ra2 {
enum class MessageFillPolicy {requestsOnly,softwareDisplay};
// Supplied host startup/surface policy. This is not the original global/UI setup.
struct MessagePresentationConfig {
    std::int32_t surfaceWidth=0,surfaceHeight=0;
    std::int32_t x=0,y=0,width=0,maximumLines=0,lineStep=0;
    std::int32_t mode=0,insertSound=0,drawSound=0;
    std::uint8_t mode3=0,mode4=0,heapFill=0xa5;
    std::uint32_t clockStart=0xffffffff,clockAccumulated=0;
    std::vector<HsvColor> colors;
    FontTextColors packing;
    MessageFillPolicy fillPolicy=MessageFillPolicy::requestsOnly;
};
struct MessageSoundRequest {std::int32_t sound;std::uint32_t flags;float volume;std::uint32_t extra;};
struct MessageFillRequest {FontTextBox box;std::uint32_t value;};
struct MessageLineRequest {std::int32_t x,y,bottom;std::uint32_t color,alpha;};
// Stable SDL-free composition owner. Shared font is immutable; every mutable
// record, link, focus, callback and pixel backing belongs to this instance.
// Fill uses an explicit surface policy; line/audio requests are recorded only.
class OwnedMessagePresentation {
    friend struct MessagePresentationInspection; // Test-only source mutation snapshots.
    std::shared_ptr<const GameFont> asset_;
    MessagePresentationConfig config_;
    MessageList list_;
    MessageListGlobals globals_;
    MessageFontMetrics metrics_;
    FontGlyphState font_;
    std::vector<std::unique_ptr<MessageNode>> nodes_;
    std::vector<std::uint16_t> pixels_;
    std::vector<const HsvColor*> colors_;
    std::uint32_t milliseconds_=0;
    MessageListServices services_;
    FontSurfaceServices surface_;
    MessageNodeDrawGlobals draw_;
    FontBlitContext blit_;
    MessageTextServices text_;
    std::vector<MessageSoundRequest> sounds_;
    std::vector<MessageFillRequest> fills_;
    std::vector<MessageLineRequest> lines_;
    const FillStoreTrace* fillObserver_=nullptr; // Borrowed only within draw().
    static void require(bool v){if(!v)throw std::invalid_argument("Message presentation ownership/domain differs");}
    std::size_t index(const MessageNode* p)const {
        for(std::size_t i=0;i<nodes_.size();++i)if(nodes_[i].get()==p)return i;
        throw std::invalid_argument("Foreign message owner");
    }
    void bind(){
        metrics_={font_.primary,font_.fallback.empty()?nullptr:font_.fallback.data(),font_.lineHeight,font_.tab,font_.spacing};
        globals_.selectedFont=&metrics_;
        colors_.clear();for(const auto& color:config_.colors)colors_.push_back(&color);
        services_.allocate=[this]{
            MessageNode* node=nullptr;
            for(const auto& p:nodes_)if(p->destroyed){node=p.get();break;}
            if(!node){nodes_.push_back(std::make_unique<MessageNode>());node=nodes_.back().get();}
            // Only untouched allocator padding is supplied; construct() writes
            // actual fields. Reuse is a host allocation policy, not guest heap parity.
            node->padding1f=config_.heapFill;node->padding42=std::uint16_t(config_.heapFill)*0x101u;
            return node;
        };
        services_.release=[this](MessageNode* p){index(p);require(p->destroyed);};
        services_.milliseconds=[this]{return milliseconds_;};
        services_.play=[this](auto s,auto f,auto v,auto e){sounds_.push_back({s,f,v,e});};
        surface_.lock=[this](auto x,auto y){require(!x&&!y);return std::span<std::uint16_t>(pixels_);};
        surface_.pitchBytes=[this]{return std::uint32_t(config_.surfaceWidth)*2;};
        surface_.width=[this]{return config_.surfaceWidth;};surface_.height=[this]{return config_.surfaceHeight;};
        surface_.unlock=[]{};
        draw_={colors_,std::int32_t(colors_.size()),&font_,&surface_,config_.drawSound};
        blit_={1,&font_,&surface_,config_.packing};
        text_.refreshIme=[this]{text_.composition.clear();text_.compositionLength=0;text_.compositionCursor=0;};
        text_.fill=[this](const auto& b,auto v){
            fills_.push_back({b,v});
            if(config_.fillPolicy==MessageFillPolicy::softwareDisplay){
                FillSurface surface;surface.width=config_.surfaceWidth;surface.height=config_.surfaceHeight;surface.words=pixels_;
                if(fillObserver_)fillDisplaySoftwareRect(surface,{b.x,b.y,b.width,b.height},v,*fillObserver_);
                else fillDisplaySoftwareRect(surface,{b.x,b.y,b.width,b.height},v);
            }
        };
        text_.line=[this](auto x,auto y,auto b,auto c,auto a){lines_.push_back({x,y,b,c,a});};
    }
public:
    OwnedMessagePresentation(std::shared_ptr<const GameFont> asset,MessagePresentationConfig config)
        :asset_(std::move(asset)),config_(std::move(config)){
        require(bool(asset_)&&config_.surfaceWidth>0&&config_.surfaceHeight>0);
        require(config_.fillPolicy==MessageFillPolicy::requestsOnly||config_.fillPolicy==MessageFillPolicy::softwareDisplay);
        const auto count=std::uint64_t(config_.surfaceWidth)*std::uint64_t(config_.surfaceHeight);
        require(count<=32*1024*1024&&config_.colors.size()<=65536);
        pixels_.resize(std::size_t(count));
        list_.x=config_.x;list_.y=config_.y;list_.width=config_.width;
        list_.maximumLines=config_.maximumLines;list_.lineStep=config_.lineStep;list_.available.fill(1);
        globals_.mode=config_.mode;globals_.mode3Enabled=config_.mode3;globals_.mode4Enabled=config_.mode4;
        globals_.clockStart=config_.clockStart;globals_.clockAccumulated=config_.clockAccumulated;globals_.sound=config_.insertSound;
        font_.primary=asset_->metrics().primary;font_.fallback=asset_->fallback();
        font_.rows=std::bit_cast<std::int32_t>(asset_->fields()[2]);
        font_.rowBytes=std::bit_cast<std::int32_t>(asset_->fields()[1]);
        font_.lineHeight=asset_->metrics().lineHeight;font_.tab=asset_->metrics().tab;font_.spacing=asset_->metrics().spacing;
        font_.clipping=true;bind();
    }
    OwnedMessagePresentation(const OwnedMessagePresentation&)=delete;
    OwnedMessagePresentation& operator=(const OwnedMessagePresentation&)=delete;
    OwnedMessagePresentation(OwnedMessagePresentation&&)=delete;
    OwnedMessagePresentation& operator=(OwnedMessagePresentation&&)=delete;
    std::unique_ptr<OwnedMessagePresentation> clone()const {
        require(!fillObserver_); // Never clone a stack-bound observer mid-draw.
        auto out=std::make_unique<OwnedMessagePresentation>(asset_,config_);
        out->pixels_=pixels_;out->list_=list_;out->globals_=globals_;out->font_=font_;
        if(!font_.surface.empty()){
            require(font_.surface.data()==pixels_.data()&&font_.surface.size()==pixels_.size());
            out->font_.surface=out->pixels_;
        }
        out->milliseconds_=milliseconds_;
        for(const auto& node:nodes_)out->nodes_.push_back(std::make_unique<MessageNode>(*node));
        const auto remap=[&](const MessageNode* node)->MessageNode*{return node?out->nodes_.at(index(node)).get():nullptr;};
        out->list_.head=remap(list_.head);
        for(auto& node:out->nodes_){node->next=remap(node->next);node->previous=remap(node->previous);}
        for(auto*& focus:out->globals_.focused)focus=remap(focus);
        // Copy values only. Never copy this-bound service or mutable-owner pointers.
        out->text_.composition=text_.composition;out->text_.compositionLength=text_.compositionLength;
        out->text_.compositionCursor=text_.compositionCursor;out->text_.extra=text_.extra;
        out->text_.highlightRgb=text_.highlightRgb;out->text_.cursorRgb=text_.cursorRgb;out->text_.cursorSuppression=text_.cursorSuppression;
        out->sounds_=sounds_;out->fills_=fills_;out->lines_=lines_;out->bind();return out;
    }
    const MessageNode* insert(const MessageInsertRequest& request){return insertMessage(list_,globals_,services_,request);}
    bool expire(){return expireMessages(list_,globals_,services_);}
    void draw(const FontGlyphTrace& trace={},const FillStoreTrace& fillTrace={}){
        require(!fillObserver_);fillObserver_=&fillTrace;
        try{drawOrdinaryMessageList(list_,globals_,draw_,services_,blit_,text_,trace);}
        catch(...){fillObserver_=nullptr;throw;}
        fillObserver_=nullptr;
    }
    void setMilliseconds(std::uint32_t value){milliseconds_=value;}
    void focus(const MessageNode* node){auto* owned=node?nodes_.at(index(node)).get():nullptr;if(owned)require(!owned->destroyed);globals_.focused[2]=owned;}
    void replacePixels(std::span<const std::uint16_t> source){require(source.size()==pixels_.size());std::copy(source.begin(),source.end(),pixels_.begin());}
    void clearRequests(){sounds_.clear();fills_.clear();lines_.clear();}
    const MessageList& list()const{return list_;}
    const MessageListGlobals& globals()const{return globals_;}
    const FontGlyphState& font()const{return font_;}
    const MessageTextServices& text()const{return text_;}
    const MessagePresentationConfig& config()const{return config_;}
    const std::shared_ptr<const GameFont>& asset()const{return asset_;}
    std::span<const std::uint16_t> pixels()const{return pixels_;}
    const auto& sounds()const{return sounds_;}
    const auto& fills()const{return fills_;}
    const auto& lines()const{return lines_;}
    std::size_t allocatedNodes()const{return nodes_.size();}
};
}
