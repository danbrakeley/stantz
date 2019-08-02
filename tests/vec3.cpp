#include "pch.h"
#include "vec3.h"

TEST(Vec3, DefaultValues) {
	{
		vec3 v;
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
		vec3 v(1, 2, 3);
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
	const vec3 v(1, 2, 3);
	const vec3 w(2, 4, 6);

	EXPECT_TRUE(unsafe_equal(v + w, vec3(3, 6, 9)));
	EXPECT_TRUE(unsafe_equal(w + v, vec3(3, 6, 9)));
	EXPECT_TRUE(unsafe_equal(v - w, vec3(-1, -2, -3)));
	EXPECT_TRUE(unsafe_equal(w - v, vec3(1, 2, 3)));

	vec3 a;
	a -= v;
	EXPECT_TRUE(unsafe_equal(a, vec3(-1, -2, -3)));
	a -= w;
	EXPECT_TRUE(unsafe_equal(a, vec3(-3, -6, -9)));

	vec3 b;
	b += v;
	EXPECT_TRUE(unsafe_equal(b, vec3(1, 2, 3)));
	b += w;
	EXPECT_TRUE(unsafe_equal(b, vec3(3, 6, 9)));

	vec3 c = v;
	EXPECT_TRUE(unsafe_equal(c *= 2.0f, vec3(2, 4, 6)));
	EXPECT_TRUE(unsafe_equal(c, vec3(2, 4, 6)));
	EXPECT_TRUE(unsafe_equal(c /= 2.0f, vec3(1, 2, 3)));
	EXPECT_TRUE(unsafe_equal(c, vec3(1, 2, 3)));
}

TEST(Vec3, Length) {
	vec3 a;
	EXPECT_EQ(a.length(), 0);
	vec3 b(1, 0, 0);
	EXPECT_EQ(b.length(), 1.0f);
	vec3 c(1, 2, 3);
	EXPECT_TRUE(almost_equal(c.length(), 3.741657f, 0.00001f, 0.00001f));
}

TEST(Vec3, LengthSquared) {
	vec3 a;
	EXPECT_EQ(a.length_squared(), 0);
	vec3 b(1, 0, 0);
	EXPECT_EQ(b.length_squared(), 1.0f);
	vec3 c(1, 2, 3);
	EXPECT_EQ(c.length_squared(), 14.0f);
}
