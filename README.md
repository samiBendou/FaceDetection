[![Build Status](https://travis-ci.org/samiBendou/FaceDetection.svg?branch=master)](https://travis-ci.org/samiBendou/FaceDetection/builds)
[![Coverage Status](https://coveralls.io/repos/github/samiBendou/FaceDetection/badge.svg?branch=master)](https://coveralls.io/github/samiBendou/FaceDetection?branch=master)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)


# FaceDetection 0.2.0

### Introduction

FaceDetection is an image processing framework. It is specially design for provide a fast implementation of Viola
and Jones method in C++.

- **High level** API to easily process and parameter filters

- **Lightweight** enough to be embedded on various microelectronic devices

The framework is based on NAlgebra framework which you can find [here](https://github.com/samiBendou/MathToolKitCPP)

### General concepts


The framework introduces a class called IMatrix which represents an image as an NPMatrix object. This allows to consider
the image as a vector and to provide all classical operations on vectors and also to provide user-friendly representation
for image processing.

The IMatrix objects are just pixel matrices but each pixel must have the same type eg. RGB.

### Install
 

### Run Unit Tests


### Additional information

**Author :** Sami Dahoux [GitHub](https://github.com/samiBendou/)

**Last Update :** 20/01/2019

**Version log :**

- 0.2.0 : Pseudo Haar features processing added
- 0.1.0 : Basic image processing features such as integral image
