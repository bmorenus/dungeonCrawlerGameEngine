// Quad-Tree data structure referenced from
// https://www.geeksforgeeks.org/quad-tree/#

#include <cmath>

struct Point {
    int x, y;

    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }

    Point() {
        x = 0;
        y = 0;
    }
};

struct Node {
    Point point;
    int data;
    Node(Point _point, int _data) {
        point = _point;
        data = _data;
    }
    Node() {
        data = 0;
    }
};

class Quad {
    Point topLeftBoundary;
    Point bottomRightBoundary;

    Node* node;

    Quad* topLeftQuadTree;
    Quad* topRightQuadTree;
    Quad* bottomLeftQuadTree;
    Quad* bottomRightQuadTree;

   public:
    Quad() {
        topLeftBoundary = Point();
        bottomRightBoundary = Point();

        node = nullptr;

        topLeftQuadTree = nullptr;
        topRightQuadTree = nullptr;
        bottomLeftQuadTree = nullptr;
        bottomRightQuadTree = nullptr;
    }

    Quad(Point _topLeftBoundary, Point _bottomRightBoundary) {
        topLeftBoundary = _topLeftBoundary;
        bottomRightBoundary = _bottomRightBoundary;

        node = nullptr;

        topLeftQuadTree = nullptr;
        topRightQuadTree = nullptr;
        bottomLeftQuadTree = nullptr;
        bottomRightQuadTree = nullptr;
    }
    void insert(Node* _node);
    Node* getClosestNode(Point _point, Point currentClosest);
    bool inBoundary(Point _point);

    void Quad::insert(Node* _node) {
        if (_node == nullptr) {
            return;
        }

        if (!inBoundary(_node->point)) {
            return;
        }

        if (abs(topLeftBoundary.x - bottomRightBoundary.x) <= 1 &&
            abs(topLeftBoundary.y - bottomRightBoundary.y) <= 1) {
            if (node == nullptr)
                node = _node;
            return;
        }

        // Indicates node is in one of the left two trees
        if ((topLeftBoundary.x + bottomRightBoundary.x) / 2 >= _node->point.x) {
            // Indicates node is in the top left tree
            if ((topLeftBoundary.y + bottomRightBoundary.y) / 2 >= _node->point.y) {
                if (topLeftQuadTree == nullptr)
                    topLeftQuadTree = new Quad(
                        Point(topLeftBoundary.x, topLeftBoundary.y),
                        Point((topLeftBoundary.x + bottomRightBoundary.x) / 2,
                              (topLeftBoundary.y + bottomRightBoundary.y) / 2));
                topLeftQuadTree->insert(_node);
            }

            // Indicates node is in the bottom left tree
            else {
                if (bottomLeftQuadTree == nullptr)
                    bottomLeftQuadTree = new Quad(
                        Point(topLeftBoundary.x,
                              (topLeftBoundary.y + bottomRightBoundary.y) / 2),
                        Point((topLeftBoundary.x + bottomRightBoundary.x) / 2,
                              bottomRightBoundary.y));
                bottomLeftQuadTree->insert(_node);
            }
            // Indicates node is in one of the right two trees
        } else {
            // Indicates node is in the top right tree
            if ((topLeftBoundary.y + bottomRightBoundary.y) / 2 >= node->point.y) {
                if (topRightQuadTree == nullptr)
                    topRightQuadTree = new Quad(
                        Point((topLeftBoundary.x + bottomRightBoundary.x) / 2,
                              topLeftBoundary.y),
                        Point(bottomRightBoundary.x,
                              (topLeftBoundary.y + bottomRightBoundary.y) / 2));
                topRightQuadTree->insert(_node);
            }

            // Indicates node is in the bottom right tree
            else {
                if (bottomRightQuadTree == NULL)
                    bottomRightQuadTree = new Quad(
                        Point((topLeftBoundary.x + bottomRightBoundary.x) / 2,
                              (topLeftBoundary.y + bottomRightBoundary.y) / 2),
                        Point(bottomRightBoundary.x, bottomRightBoundary.y));
                bottomRightQuadTree->insert(_node);
            }
        }
    }

    Node* Quad::getClosestNode(Point _point, Node* currentClosest) {
        // Current quad cannot contain it
        if (!inBoundary(_point))
            return nullptr;

        // We are at a quad of unit length
        // We cannot subdivide this quad further
        if (node != nullptr)
            return currentClosest;

        if ((topLeftBoundary.x + bottomRightBoundary.x) / 2 >= _point.x) {
            // Indicates topLeftTree
            if ((topLeftBoundary.y + bottomRightBoundary.y) / 2 >= _point.y) {
                if (topLeftQuadTree == nullptr)
                    return nullptr;
                return topLeftQuadTree->getClosestNode(_point, );
            }

            // Indicates botLeftTree
            else {
                if (bottomLeftQuadTree == nullptr)
                    return nullptr;
                return bottomLeftQuadTree->search(_point);
            }
        } else {
            // Indicates topRightTree
            if ((topLeftBoundary.y + bottomRightBoundary.y) / 2 >= _point.y) {
                if (topRightQuadTree == nullptr)
                    return nullptr;
                return topRightQuadTree->search(_point);
            }

            // Indicates botRightTree
            else {
                if (bottomRightQuadTree == nullptr)
                    return nullptr;
                return bottomRightQuadTree->search(_point);
            }
        }
    };

    bool Quad::inBoundary(Point _point) {
        return (_point.x >= topLeftBoundary.x &&
                _point.x <= bottomRightBoundary.x &&
                _point.y >= topLeftBoundary.y &&
                _point.y <= bottomRightBoundary.y);
    }
};
