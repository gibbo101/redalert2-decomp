// TRect<T>, four scalar coordinates; RTTI VectorClass<TRect<int>>.
#ifndef RA2_SHARED_TRECT_HPP
#define RA2_SHARED_TRECT_HPP
template<class T> class TRect {
public:
    TRect() {}
    TRect(T x, T y, T width, T height) : X(x), Y(y), Width(width), Height(height) {}
    bool operator==(TRect const &other) const {
        return X == other.X && Y == other.Y && Width == other.Width && Height == other.Height;
    }
    bool operator!=(TRect const &other) const { return !(*this == other); }
    T X, Y, Width, Height;
};
#endif
