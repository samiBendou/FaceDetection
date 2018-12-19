/**
 * @class          : Pixel
 * @date           : 19/12/2018
 * @author         : samiBendou
 * @description    : Pixel class is a representation of a pixel providing uses of multiple color scale
 *                   and conversion between theses.
 *
 * @license        : Dahoux Sami 2018 - © Copyright All Rights Reserved.
 */

#ifndef FACEDETECTION_PIXEL_H
#define FACEDETECTION_PIXEL_H

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <typedef.h>

#define MAX_LIMIT_CMP 255


class Pixel {

public:

    enum Format {
        GScale = 1, RGB = 3
    };

    friend Pixel abs(const Pixel &p);

    friend Pixel sqrt(const Pixel &p);

    // CONSTRUCTOR

    explicit Pixel(Format format = RGB, bool limited = false);

    Pixel(int grey);

    explicit Pixel(int grey, bool limited);

    Pixel(int red, int green, int blue, bool limited = false);

    // GETTERS

    int red() const;

    int green() const;

    int blue() const;

    int greyScale() const;

    bool limited() const;

    Format format() const;

    // SETTERS

    void setRed(int red);

    void setGreen(int green);

    void setBlue(int blue);

    void setGreyScale(int grey);

    void setRGB(int red, int green, int blue);

    void setLimited(bool limited);

    // MANIPULATORS

    void limit();

    // OPERATORS

    friend Pixel operator+(const Pixel &p1, const Pixel &p2);

    friend Pixel operator+(const Pixel &p, int val);

    friend Pixel operator+(int val, const Pixel &p);

    friend Pixel operator-(const Pixel &p1, const Pixel &p2);

    friend Pixel operator-(const Pixel &p, int val);

    friend Pixel operator-(int val, const Pixel &p);

    Pixel operator-() const;

    friend Pixel operator*(const Pixel &p1, const Pixel &p2);

    friend Pixel operator*(const Pixel &p, int val);

    friend Pixel operator*(int val, const Pixel &p);

    friend Pixel operator/(const Pixel &p1, const Pixel &p2);

    friend Pixel operator/(const Pixel &p, int val);

    friend Pixel operator/(int val, const Pixel &p);

    Pixel &operator+=(const Pixel &p);

    Pixel &operator*=(const Pixel &p);

    Pixel &operator-=(const Pixel &p);

    Pixel &operator/=(const Pixel &p);

    friend bool operator==(const Pixel &p, int val);

    friend bool operator==(const Pixel &p1, const Pixel &p2);

    friend bool operator!=(const Pixel &p1, const Pixel &p2);

    friend bool operator>(const Pixel &p1, const Pixel &p2);

    friend bool operator<(const Pixel &p1, const Pixel &p2);

    friend bool operator>=(const Pixel &p1, const Pixel &p2);

    friend bool operator<=(const Pixel &p1, const Pixel &p2);

    friend std::ostream &operator<<(std::ostream &os, const Pixel &p);

private:

    // ALGEBRAICAL OPERATIONS

    void add(const Pixel &p);

    void sub(const Pixel &p);

    void opp();

    void prod(const Pixel &p);

    void div(const Pixel &p);

    bool isEqual(int val) const;

    int limitIfLimited(int cmp) const;

    void conformFormatTo(const Pixel& p);

    void setPrivateRGB(int red, int green, int blue);

    int _red;
    int _green;
    int _blue;

    Format _format;
    bool _limited;
};


#endif //FACEDETECTION_PIXEL_H
