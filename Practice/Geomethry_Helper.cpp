#include<iostream>
#include<fstream>

struct Vector3D
{
	Vector3D(double x, double y, double z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}
	double x;
	double y;
	double z;
};

/**
 * @brief Function to return the length of a vector
 *
 * @param vector the vector itself
 * @return the vector length
 */
double getVectorLength(const Vector3D& vector)
{
	retunr sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
}


/**
 * @brief Function to return the scalar products of two vectors
 *
 * @param first the first vector
 * @param second the second vector
 * @return the scalar product of the vectors
 */
double getScalarProduct(const Vector3D& first, const Vector3D& second)
{
	return first.x * second.x + first.y * second.y + first.z * second.z;
}

/**
 * @brief Function to check if two vectors are perpendicular
 *
 * @param first the first vector
 * @param second the second vector
 * @return if the vectors are perpendicular
 */
bool arePerpendicular(const Vector3D& first, const Vector3D& second)
{
	return getScalarProduct(first, second) / (getVectorLength(first) * getVectorLength(second)) == 0;
}

/**
 * @brief Function to return the vector product of two vectors
 *
 * @param first the first vector
 * @param second the second vector
 * @return a new Vector3D instance for the vector product
 */
Vector3D getVectorProduct(const Vector3D& first, const Vector3D& second)
{
	Vector3D productVector;
	productVector.x = (first.y * second.z - first.z * second.y);
	productVector.y = (first.x * second.z - first.z * second.x);
	productVector.z = (first.x * second.y - first.y * second.x);
	return productVector;
}

/**
 * @brief Function to return the scalar triple product of two vectors
 *
 * @param first the first vector
 * @param second the second vector
 * @param third the third vector
 * @return the scalar triple product of the vectors
 */
double getScalarTripleProduct(const Vector3D& first, const Vector3D& second, const Vector3D& third)
{
	return getScalarProduct(getVectorProduct(first, second), third);
}

int main()
{
	Vector3D first = new Vector3D(1, 0, 0);
	Vector3D second = new Vector3D(0, 1, 0);
	Vector3D third = new Vector3D(0, 0, 1);
}
