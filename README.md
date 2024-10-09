# 3D Vision and Video (IMA208) - 2023/2024

## Course Overview

This repository contains materials and resources for the course **IMA208: 3D Vision and Video**, part of the **Image-Data-Signal** curriculum. The course explores techniques for acquiring images in both temporal (video) and spatial (3D) domains. Topics covered include motion estimation, object tracking, stereo vision, and 3D point cloud reconstruction, using a hands-on, flipped classroom approach.

### Key Topics:

- Motion Estimation in Video: Optical flow, block matching, and parametric motion estimation, including deep learning techniques.
- Object Tracking: Kalman filtering, particle filtering, and automated tracking in video.
- Stereo Vision and 3D Reconstruction: Techniques for obtaining 3D information from stereo images and point clouds.
- 3D Point Clouds: Processing and surface reconstruction from 3D data.

## Prerequisites

Students are expected to have:
- Basic knowledge of image processing and computer vision
- Familiarity with programming, particularly in Python

## Course Structure

- Total Hours: 24 hours of in-person sessions (16 sessions).
- Credits: 2.5 ECTS
- Evaluation: 
  - Short quizzes (QCM) at the beginning of each session.
  - Practical work (graded).
  - Final exam based on discussions and work done during the flipped classroom sessions.

## Instructor

- Professor Christophe Kervazo

## Installation and Setup

Some exercises and projects require Python and relevant image processing libraries. You can follow the instructions below to set up your environment using `conda`:

1. Anaconda/Miniconda: Download and install Python with Anaconda or Miniconda from [Conda Official Site](https://docs.conda.io/en/latest/).
2. Image Processing Libraries: Create a new conda environment with the necessary packages:
   ```bash
   conda create -n ima python matplotlib numpy scipy scikit-image ipykernel pandas scikit-learn jupyter tqdm bokeh opencv munkres
   ```
3. Activate the environment:
   ```bash
   conda activate ima
   ```

4. Launch Jupyter Notebook (if required for exercises):
   ```bash
   jupyter notebook
   ```

This will set up the necessary environment for running image processing tasks and exercises for the course.

## How to Contribute

Feel free to contribute to the repository by:
- Submitting pull requests for corrections or improvements.
- Providing additional examples or extending the projects.
