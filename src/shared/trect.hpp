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
#ifdef RA2_TRECT_POINT_MEMBERS
    void Set(T x, T y, T w, T h) { X = x; Y = y; Width = w; Height = h; }
    TRect(Point2D const &point, T w, T h) : X(point.X), Y(point.Y), Width(w), Height(h) {}
    bool Is_Valid() const { return Width > 0 && Height > 0; }
    bool Is_Point_Within(Point2D const &point) const
    {
        return point.X >= X && point.X < X + Width && point.Y >= Y && point.Y < Y + Height;
    }
#endif
    T X, Y, Width, Height;
};
#endif
