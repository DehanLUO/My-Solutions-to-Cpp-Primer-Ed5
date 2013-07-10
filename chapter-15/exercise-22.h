/*
 * Exercise 15.22: For the class you chose in the previous exercise, identify
 * some of the likely virtual functions as well as public and protected members.
 */

#ifndef CHAPTER_15_EXERCISE_22_H_
#define CHAPTER_15_EXERCISE_22_H_

#include <math.h>  // M_PI

#include <iostream>  // std::ostream, std::cout
#include <string>    // std::string

class GeometricPrimitive {
 public:
  /**
   * @brief Virtual destructor for proper polymorphic cleanup
   */
  virtual ~GeometricPrimitive() = default;

  /**
   * @brief Calculate surface area of the geometric primitive
   * @return Surface area as double value
   * @note Pure virtual function must be implemented by derived classes
   */
  virtual double CalculateSurfaceArea() const = 0;

  /**
   * @brief Calculate volume of the geometric primitive
   * @return Volume as double value
   * @note Pure virtual function must be implemented by derived classes
   */
  virtual double CalculateVolume() const = 0;

  /**
   * @brief Get descriptive name of the geometric primitive
   * @return String representing the primitive type
   */
  virtual std::string GetName() const = 0;

  /**
   * @brief Display information about the geometric primitive
   * @param ostream Output stream for display
   * @note Provides formatted output of primitive properties
   */
  virtual void Display(std::ostream& ostream = std::cout) const {
    ostream << GetName() << ":\n";
    ostream << "  Surface Area: " << CalculateSurfaceArea() << " units²\n";  //
    ostream << "  Volume: " << CalculateVolume() << " units³\n";
  }
};

/**
 * @class Shape2D
 * @brief Abstract base class for two-dimensional geometric primitives
 * @note Specializes interface for 2D shapes (no volume)
 */
class Shape2D : public GeometricPrimitive {
 public:
  /**
   * @brief Calculate volume (always 0 for 2D shapes)
   * @return 0.0 since 2D shapes have no volume
   */
  double CalculateVolume() const override { return 0.0; }

  /**
   * @brief Calculate perimeter of the 2D shape
   * @return Perimeter as double value
   * @note Pure virtual function for 2D-specific property
   */
  virtual double CalculatePerimeter() const = 0;

  /**
   * @brief Display information about the 2D shape
   * @param os Output stream for display
   */
  void Display(std::ostream& os = std::cout) const override {
    os << GetName() << " (2D):\n";
    os << "  Area: " << CalculateSurfaceArea() << " units²\n";  //
    os << "  Perimeter: " << CalculatePerimeter() << " units\n";
  }
};

/**
 * @class Shape3D
 * @brief Abstract base class for three-dimensional geometric primitives
 * @note Specializes interface for 3D shapes with volume
 */
class Shape3D : public GeometricPrimitive {
 public:
  /**
   * @brief Calculate surface area to volume ratio
   * @return Ratio of surface area to volume
   * @note Useful metric for many physical properties
   */
  virtual double CalculateSurfaceToVolumeRatio() const {
    return CalculateSurfaceArea() / CalculateVolume();
  }

  /**
   * @brief Display information about the 3D shape
   * @param os Output stream for display
   */
  void Display(std::ostream& os = std::cout) const override {
    os << GetName() << " (3D):\n";
    os << "  Surface Area: " << CalculateSurfaceArea() << " units²\n";  //
    os << "  Volume: " << CalculateVolume() << " units³\n";             //
    os << "  Surface/Volume Ratio: " << CalculateSurfaceToVolumeRatio() << "\n";
  }
};

/**
 * @class Circle
 * @brief Concrete class representing a circle
 * @note Derived from Shape2D with radius parameter
 */
class Circle : public Shape2D {
 public:
  /**
   * @brief Parameterized constructor
   * @param radius Radius of the circle
   */
  explicit Circle(double radius) : radius_(radius) {}

  /**
   * @brief Calculate area of the circle
   * @return Area as π * radius²
   */
  double CalculateSurfaceArea() const override {
    return M_PI * radius_ * radius_;
  }

  /**
   * @brief Calculate perimeter (circumference) of the circle
   * @return Circumference as 2 * π * radius
   */
  double CalculatePerimeter() const override { return 2 * M_PI * radius_; }

  /**
   * @brief Get descriptive name
   * @return "Circle"
   */
  std::string GetName() const override { return "Circle"; }

  /**
   * @brief Get radius of the circle
   * @return Radius value
   */
  double GetRadius() const { return radius_; }

 private:
  double radius_;
};

/**
 * @class Box
 * @brief Concrete class representing a rectangular box (3D)
 * @note Derived from Shape3D with length, width, height parameters
 */
class Box : public Shape3D {
 public:
  /**
   * @brief Parameterized constructor
   * @param length Length of the box
   * @param width Width of the box
   * @param height Height of the box
   */
  Box(double length, double width, double height)
      : length_(length), width_(width), height_(height) {}

  /**
   * @brief Calculate surface area of the box
   * @return Surface area as 2*(l*w + l*h + w*h)
   */
  double CalculateSurfaceArea() const override {
    return 2 * (length_ * width_ + length_ * height_ + width_ * height_);
  }

  /**
   * @brief Calculate volume of the box
   * @return Volume as length * width * height
   */
  double CalculateVolume() const override { return length_ * width_ * height_; }

  /**
   * @brief Get descriptive name
   * @return "Box"
   */
  std::string GetName() const override { return "Box"; }

 private:
  double length_;
  double width_;
  double height_;
};

/**
 * @class Sphere
 * @brief Concrete class representing a sphere
 * @note Derived from Shape3D with radius parameter
 */
class Sphere : public Shape3D {
 public:
  /**
   * @brief Parameterized constructor
   * @param radius Radius of the sphere
   */
  explicit Sphere(double radius) : radius_(radius) {}

  /**
   * @brief Calculate surface area of the sphere
   * @return Surface area as 4 * π * radius²
   */
  double CalculateSurfaceArea() const override {
    return 4 * M_PI * radius_ * radius_;
  }

  /**
   * @brief Calculate volume of the sphere
   * @return Volume as (4/3) * π * radius³
   */
  double CalculateVolume() const override {
    return (4.0 / 3.0) * M_PI * radius_ * radius_ * radius_;
  }

  /**
   * @brief Get descriptive name
   * @return "Sphere"
   */
  std::string GetName() const override { return "Sphere"; }

 private:
  double radius_;
};

/**
 * @class Cone
 * @brief Concrete class representing a right circular cone
 * @note Derived from Shape3D with radius and height parameters
 */
class Cone : public Shape3D {
 public:
  /**
   * @brief Parameterized constructor
   * @param radius Base radius of the cone
   * @param height Height of the cone
   */
  Cone(double radius, double height) : radius_(radius), height_(height) {}

  /**
   * @brief Calculate surface area of the cone
   * @return Surface area as π*r*(r + √(h² + r²))
   */
  double CalculateSurfaceArea() const override {
    double slant_height = std::sqrt(height_ * height_ + radius_ * radius_);
    return M_PI * radius_ * (radius_ + slant_height);
  }

  /**
   * @brief Calculate volume of the cone
   * @return Volume as (1/3) * π * r² * h
   */
  double CalculateVolume() const override {
    return (1.0 / 3.0) * M_PI * radius_ * radius_ * height_;
  }

  /**
   * @brief Get descriptive name
   * @return "Cone"
   */
  std::string GetName() const override { return "Cone"; }

 private:
  double radius_;
  double height_;
};

#endif  // CHAPTER_15_EXERCISE_22_H_