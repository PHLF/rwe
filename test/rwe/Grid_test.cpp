#include <catch.hpp>
#include <optional>
#include <rwe/Grid.h>

namespace rwe
{
    TEST_CASE("Grid")
    {
        SECTION("when constructed")
        {
            Grid<int> g(3, 4);

            SECTION("has the given width and height")
            {
                REQUIRE(g.getWidth() == 3);
                REQUIRE(g.getHeight() == 4);
            }

            SECTION("can be written to")
            {
                g.get(0, 0) = 2;
                g.get(2, 3) = 10;
                REQUIRE(g.get(0, 0) == 2);
                REQUIRE(g.get(2, 3) == 10);
            }
        }

        SECTION("zero-argument ctor")
        {
            SECTION("constructs an empty grid")
            {
                Grid<int> g;
                REQUIRE(g.getWidth() == 0);
                REQUIRE(g.getHeight() == 0);
            }
        }

        SECTION("initial value ctor")
        {
            SECTION("fills the grid with the initial value")
            {
                Grid<int> g(3, 4, 5);
                REQUIRE(g.getWidth() == 3);
                REQUIRE(g.getHeight() == 4);
                for (int y = 0; y < 4; ++y)
                {
                    for (int x = 0; x < 3; ++x)
                    {
                        REQUIRE(g.get(x, y) == 5);
                    }
                }
            }
        }

        SECTION("vector ctor")
        {
            SECTION("constructs grid from existing data")
            {
                Grid<int> g(3, 2, {1, 2, 3, 4, 5, 6});
                REQUIRE(g.get(0, 0) == 1);
                REQUIRE(g.get(1, 0) == 2);
                REQUIRE(g.get(2, 0) == 3);
                REQUIRE(g.get(0, 1) == 4);
                REQUIRE(g.get(1, 1) == 5);
                REQUIRE(g.get(2, 1) == 6);
            }
        }

        SECTION(".replace")
        {
            SECTION("Copies the given grid into this one")
            {
                Grid<int> g(3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                Grid<int> g2(2, 3, {60, 61, 62, 63, 64, 65});

                g.replace(1, 0, g2);

                REQUIRE(g.get(0, 0) == 1);
                REQUIRE(g.get(1, 0) == 60);
                REQUIRE(g.get(2, 0) == 61);
                REQUIRE(g.get(0, 1) == 4);
                REQUIRE(g.get(1, 1) == 62);
                REQUIRE(g.get(2, 1) == 63);
                REQUIRE(g.get(0, 2) == 7);
                REQUIRE(g.get(1, 2) == 64);
                REQUIRE(g.get(2, 2) == 65);
                REQUIRE(g.get(0, 3) == 10);
                REQUIRE(g.get(1, 3) == 11);
                REQUIRE(g.get(2, 3) == 12);
            }

            SECTION("Throws if the new grid goes over max x")
            {
                Grid<int> g(3, 4);
                Grid<int> g2(2, 1);
                REQUIRE_THROWS(g.replace(2, 0, g2));
            }

            SECTION("Throws if the new grid goes over max y")
            {
                Grid<int> g(3, 4);
                Grid<int> g2(1, 3);
                REQUIRE_THROWS(g.replace(0, 2, g2));
            }
        }
        SECTION(".transformAndReplace")
        {
            SECTION("Works with a transformation function")
            {
                Grid<int> g(3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                Grid<std::string> g2(2, 3, {"60", "61", "62", "63", "64", "65"});

                g.transformAndReplace<std::string>(1, 0, g2, [](const std::string& x) { return std::stoi(x); });

                REQUIRE(g.get(0, 0) == 1);
                REQUIRE(g.get(1, 0) == 60);
                REQUIRE(g.get(2, 0) == 61);
                REQUIRE(g.get(0, 1) == 4);
                REQUIRE(g.get(1, 1) == 62);
                REQUIRE(g.get(2, 1) == 63);
                REQUIRE(g.get(0, 2) == 7);
                REQUIRE(g.get(1, 2) == 64);
                REQUIRE(g.get(2, 2) == 65);
                REQUIRE(g.get(0, 3) == 10);
                REQUIRE(g.get(1, 3) == 11);
                REQUIRE(g.get(2, 3) == 12);
            }

            SECTION("Throws if the new grid goes over max x")
            {
                Grid<int> g(3, 4);
                Grid<int> g2(2, 1);
                REQUIRE_THROWS(g.transformAndReplace<int>(2, 0, g2, [](int i) { return i; }));
            }

            SECTION("Throws if the new grid goes over max y")
            {
                Grid<int> g(3, 4);
                Grid<int> g2(1, 3);
                REQUIRE_THROWS(g.transformAndReplace<int>(0, 2, g2, [](int i) { return i; }));
            }
        }

        SECTION(".set")
        {
            SECTION("Sets the given area to the given value")
            {
                Grid<int> g(3, 4, 5);

                g.set(GridRegion(0, 1, 3, 2), 8);

                REQUIRE(g.get(0, 0) == 5);
                REQUIRE(g.get(1, 0) == 5);
                REQUIRE(g.get(2, 0) == 5);
                REQUIRE(g.get(0, 1) == 8);
                REQUIRE(g.get(1, 1) == 8);
                REQUIRE(g.get(2, 1) == 8);
                REQUIRE(g.get(0, 2) == 8);
                REQUIRE(g.get(1, 2) == 8);
                REQUIRE(g.get(2, 2) == 8);
                REQUIRE(g.get(0, 3) == 5);
                REQUIRE(g.get(1, 3) == 5);
                REQUIRE(g.get(2, 3) == 5);
            }
        }

        SECTION(".tryGet")
        {
            SECTION("gets if the cell is inside the grid")
            {
                Grid<int> g(3, 2, {1, 2, 3, 4, 5, 6});

                // inside points
                REQUIRE(g.tryGet(Point(0, 0)) == std::optional<int>(1));
                REQUIRE(g.tryGet(Point(1, 0)) == std::optional<int>(2));
                REQUIRE(g.tryGet(Point(2, 0)) == std::optional<int>(3));
                REQUIRE(g.tryGet(Point(0, 1)) == std::optional<int>(4));
                REQUIRE(g.tryGet(Point(1, 1)) == std::optional<int>(5));
                REQUIRE(g.tryGet(Point(2, 1)) == std::optional<int>(6));

                // outside points
                REQUIRE(g.tryGet(Point(-1, 0)) == std::nullopt);
                REQUIRE(g.tryGet(Point(0, -1)) == std::nullopt);
                REQUIRE(g.tryGet(Point(3, 0)) == std::nullopt);
                REQUIRE(g.tryGet(Point(0, 2)) == std::nullopt);
            }
        }

        SECTION(".clampToCoords")
        {
            SECTION("Returns the coords when they are in the grid")
            {
                Grid<int> g(3, 2);
                REQUIRE(g.clampToCoords(Point(0, 0)) == GridCoordinates(0, 0));
                REQUIRE(g.clampToCoords(Point(0, 1)) == GridCoordinates(0, 1));
                REQUIRE(g.clampToCoords(Point(1, 0)) == GridCoordinates(1, 0));
            }

            SECTION("clamps when points are outside")
            {
                Grid<int> g(3, 2);
                REQUIRE(g.clampToCoords(Point(-1, 1)) == GridCoordinates(0, 1)); // left
                REQUIRE(g.clampToCoords(Point(3, 1)) == GridCoordinates(2, 1));  // right
                REQUIRE(g.clampToCoords(Point(2, -1)) == GridCoordinates(2, 0)); // up
                REQUIRE(g.clampToCoords(Point(2, 2)) == GridCoordinates(2, 1));  // down

                REQUIRE(g.clampToCoords(Point(-1, -1)) == GridCoordinates(0, 0)); // topleft
                REQUIRE(g.clampToCoords(Point(3, -1)) == GridCoordinates(2, 0));  // topright
                REQUIRE(g.clampToCoords(Point(-1, 2)) == GridCoordinates(0, 1));  // bottomleft
                REQUIRE(g.clampToCoords(Point(3, 2)) == GridCoordinates(2, 1));   // bottomright
            }
        }
    }
}
