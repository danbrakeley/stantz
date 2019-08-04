#include "pch.h"
#include "math/vec3.h"

TEST(Vec3, DefaultValues) {
	{
		Vec3 v;
		EXPECT_EQ(v.x(), 0);
		EXPECT_EQ(v.y(), 0);
		EXPECT_EQ(v.z(), 0);
		EXPECT_EQ(v.r(), 0);
		EXPECT_EQ(v.g(), 0);
		EXPECT_EQ(v.b(), 0);
		EXPECT_EQ(v[0], 0);
		EXPECT_EQ(v[1], 0);
		EXPECT_EQ(v[2], 0);
	}

	{
		Vec3 v(1, 2, 3);
		EXPECT_EQ(v.x(), 1);
		EXPECT_EQ(v.y(), 2);
		EXPECT_EQ(v.z(), 3);
		EXPECT_EQ(v.r(), 1);
		EXPECT_EQ(v.g(), 2);
		EXPECT_EQ(v.b(), 3);
		EXPECT_EQ(v[0], 1);
		EXPECT_EQ(v[1], 2);
		EXPECT_EQ(v[2], 3);
	}
}

TEST(Vec3, BasicMath) {
	const Vec3 v(1, 2, 3);
	const Vec3 w(2, 4, 6);

	EXPECT_TRUE(unsafe_equal(v + w, Vec3(3, 6, 9)));
	EXPECT_TRUE(unsafe_equal(w + v, Vec3(3, 6, 9)));
	EXPECT_TRUE(unsafe_equal(v - w, Vec3(-1, -2, -3)));
	EXPECT_TRUE(unsafe_equal(w - v, Vec3(1, 2, 3)));

	Vec3 a;
	a -= v;
	EXPECT_TRUE(unsafe_equal(a, Vec3(-1, -2, -3)));
	a -= w;
	EXPECT_TRUE(unsafe_equal(a, Vec3(-3, -6, -9)));

	Vec3 b;
	b += v;
	EXPECT_TRUE(unsafe_equal(b, Vec3(1, 2, 3)));
	b += w;
	EXPECT_TRUE(unsafe_equal(b, Vec3(3, 6, 9)));

	Vec3 c = v;
	EXPECT_TRUE(unsafe_equal(c *= 2.0f, Vec3(2, 4, 6)));
	EXPECT_TRUE(unsafe_equal(c, Vec3(2, 4, 6)));
	EXPECT_TRUE(unsafe_equal(c /= 2.0f, Vec3(1, 2, 3)));
	EXPECT_TRUE(unsafe_equal(c, Vec3(1, 2, 3)));
}

TEST(Vec3, Length) {
	Vec3 a;
	EXPECT_EQ(a.length(), 0);
	Vec3 b(1, 0, 0);
	EXPECT_EQ(b.length(), 1.0f);
	Vec3 c(1, 2, 3);
	EXPECT_TRUE(nearly_equal(c.length(), 3.741657f, 0.00001f, 0.00001f));
}

TEST(Vec3, LengthSquared) {
	Vec3 a;
	EXPECT_EQ(a.length_squared(), 0);
	Vec3 b(1, 0, 0);
	EXPECT_EQ(b.length_squared(), 1.0f);
	Vec3 c(1, 2, 3);
	EXPECT_EQ(c.length_squared(), 14.0f);
}

TEST(Vec3, Dot) {
	EXPECT_EQ(dot(Vec3(1, 2, 3), Vec3(4, -5, 6)), 12);
}

TEST(Vec3, Reflect) {
	EXPECT_TRUE(unsafe_equal(reflect(Vec3(1, -1, 0), Vec3(0, 1, 0)), Vec3(1, 1, 0)));
}
