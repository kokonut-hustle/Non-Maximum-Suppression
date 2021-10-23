

struct Point
{
    double x, y;

    Point() : x(0), y(0) {}

    Point(double _x, double _y) : x(_x),
                                  y(_y)
    {
    }
};

// Bounding Box
struct BBOX
{
    Point upper_right;
    Point lower_left;
    double score;

    BBOX() : upper_right(), lower_left(), score(0.0) {}

    BBOX(Point _upper_right, Point _lower_left, double _score) : upper_right(_upper_right),
                                                                lower_left(_lower_left),
                                                                score(_score)
    {
    }
};

BBOX intersect(const BBOX &box1, const BBOX &box2)
{
    const double &max_x1 = box1.upper_right.x, &max_y1 = box1.lower_left.y;
    const double &max_x2 = box2.upper_right.x, &max_y2 = box2.lower_left.y;
    const double &min_x1 = box1.lower_left.x, &min_y1 = box1.upper_right.y;
    const double &min_x2 = box2.lower_left.x, &min_y2 = box2.upper_right.y;

    if (max_x1 <= min_x2 || max_x2 <= min_x1 || max_y1 <= min_y2 || max_y2 <= min_y1)
        return BBOX();

    Point upper_right(std::max(max_x1, max_x2), std::min(min_y1, min_y2));
    Point lower_left(std::min(min_x1, min_x2), std::max(max_y1, max_y2));

    return BBOX(upper_right, lower_left, 0.0);
}

inline double area(const BBOX &box) {
    return (box.upper_right.x - box.lower_left.x) * (box.lower_left.y - box.upper_right.y);
}

double IOU(const BBOX &box1, const BBOX &box2)
{
    double intersect_area = area(intersect(box1, box2));
    double union_area = area(box1) - intersect_area + area(box2);
    
    return intersect_area / union_area;
}
