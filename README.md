# 🧠 DetectNClassify  
**Classical Image Segmentation and Object Detection in C++**

---

## 📌 Project Description
**DetectNClassify** is a C++ project that implements a **classical image processing pipeline** for **image segmentation and object detection** without using deep learning.

The project processes an input image step by step using **histogram analysis**, **K-Means clustering**, and **connected component segmentation** to detect and visualize individual objects.

All core algorithms are implemented **from scratch**, while **OpenCV** is used only for image loading, resizing, and visualization.

---

## 🎯 Objectives
- Convert RGB images to grayscale manually  
- Extract grayscale intensity histograms  
- Apply **K-Means-based thresholding**  
- Generate binary images  
- Perform connected component segmentation  
- Group and visualize detected objects  

---

## 🛠 Technologies Used
- **C++**
- **OpenCV**
- **CMake**
- Classical Computer Vision Algorithms
- Manual Memory Management

---

## 📂 Project Structure

DetectNClassify
├── include
│ ├── histogram.h
│ ├── kmean.h
│ └── segment.h
├── src
│ ├── main.cpp
│ ├── histogram.cpp
│ ├── kmean.cpp
│ └── segment.cpp
└── CMakeLists.txt

## ⚙️ Processing Pipeline

### 1️⃣ Image Loading
- Loads an RGB image using OpenCV
- Resizes it to **640 × 640**
- Stores pixel values in a manually allocated 1D array

---

### 2️⃣ Grayscale Conversion
The RGB image is converted to grayscale using:


---

### 3️⃣ Histogram Calculation
- Computes the grayscale intensity histogram
- Histogram values are used as input for K-Means clustering

---

### 4️⃣ K-Means Thresholding
- Applies **K-Means clustering** on histogram data
- Determines optimal threshold values
- Converts the grayscale image into a **binary image**

---

### 5️⃣ Binary Segmentation
- Separates foreground and background regions
- Produces a binary image representation

---

### 6️⃣ Connected Component Segmentation
- Labels connected regions as individual objects
- Each detected region represents a separate object

---

### 7️⃣ Object Grouping & Visualization
- Groups pixels belonging to the same object
- Assigns different colors to each object
- Displays segmentation results clearly

---

## 🖼 Output Windows
The application displays the following stages sequentially:
- Original Image
- Grayscale Image
- Binary Image
- Segmented Image
- Color-Grouped Objects

---

## 🚀 Build & Run

### Requirements
- C++ compiler (C++11 or newer)
- OpenCV
- CMake

### Build
```bash
mkdir build
cd build
cmake ..
make

### RUN
./DetectNClassify

