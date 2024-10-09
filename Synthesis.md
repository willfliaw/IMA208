# Synthesis

## Motion estimation

- 2D motion field : projection of the 3D movement to a plane
- Optical flow : apparent motion of a luminance pattern
- Motion is observed based on color / luminance variations
- Requires two assumptions
  - Constant color / illumination hypothesis (CIH) : the object appearance does not change too much with time
    - $f(x, y, t + T ) = f(x − c(x, y), y − d(x, y), t)$
  - Small motion : points do not move too far
    - $f_t+uf_x+vf_v=0$, $u=\lim\limits_{T\rightarrow 0}\frac{c(x, y)}{T}$, $v=\lim\limits_{T\rightarrow 0}\frac{d(x, y)}{T}$
      - Aperture problem: flow perpendicular to $\nabla f$ cannot be determined
- In practice (with noise): $\arg\min\limits_{u, v}(D(f_0, f_1, (u, v)) + R(u, v))$
  - Total variation (Horn and Schunck): $\min\limits_{u, v}\iint_\mathcal{R}(f_t+uf_x+vf_v=0)^2dxdy+\lambda\iint_\mathcal{R}\mathcal\|\nabla u\|^2+\|\nabla v\|^2dxdy$
    - $\begin{cases}\lambda\nabla^2 u = f_x(f_t+uf_x+vf_v)\\\lambda\nabla^2 v = f_y(f_t+uf_x+vf_v)\end{cases}$
  - Lucas Kanade: Increase the number of equations by taking a pixel neighborhood $(x_i, y_i)_{i=1}^n$
    - $\min\limits_{u,v}\sum\limits_{i=1,\dots,n}w_i\left(f_t(x_i, y_i)+uf_x(x_i, y_i)+vf_v(x_i, y_i)\right)^2$
    - For larger motions one could process iteratively by reducing the images resolutions
  - Both methods yield bad results close to object boundaries
- Block matching: minimize dissimilarity measure of the vector of the luminance values in the different pixels of a block $f_t(B_{p,q})$ and $f_k(B_{p+\hat{i},q+\hat{j}})$, where $(\hat{i},\hat{j})$ is the estimated motion vector of the block $B_{p,q}$
  - $(\hat{i},\hat{j})=\arg\min\limits_{(i, j)\in\mathcal{W}}d(f_t(B_{p,q}),f_k(B_{p-i,q-j}))$
  - Dissimilarity measures:
    - Euclidean distance
    - Sum of squared differences
      - Not robust to outliers
      - Does not take into account global illumination changes
      - If illumination does not depend on the patch (unrealistic), can be quickly computed using FFT: $(\hat{i}, \hat{j})=\arg\max\limits_{(i,j)\in\mathcal{W}}\langle f_t(B_{p,q}), f_k(B_{p-i,q-j})\rangle$
        - Correlation could be normalized
    - Sum of absolute differences ($l_1$ norm)
      - $l_2$ norm yields smaller prediction error, but less smooth motion field (higher coding cost, artefacts; could be solved with regularized cost function)
- Block matching algorithms:
  - Naive option: test all possible $i, j$
  - Slightly better approach: focus on a neighborhood $\mathcal{A}$
  - Fast methods: only test a subset of $\mathcal{W}$
    - 2D logarithmic search: start with broad search window, at each iteration either stay on center with $r_{k+1}=\frac{r_k}{2}$ or move the center at $(i_k, j_j)$
    - 3 Step search: fix number of iterations (3)
    - Cross search: The search is first performed horizontally and we continue in this direction as long as the current best vector is different from the center of the window and we do not reach a picture boundary. Then, we redo the same vertically
    - Diamond search: Start with the LDSP and switch to the SDSP when the central vector of is selected (otherwise, move the pattern). After one iteration with the SDSP, the algorithm is stopped
    - Hexagon search: uniform displacement speed
- Subpixel motion estimation: interpolation
- Block size
  - Use smaller blocks
  - Use variable-size block matching
- Parametric motion estimation
  - Indirect: estimate a dense motion field and then fit a parametric global motion model on it
  - Direct: the parameters are directly introduced in the estimation phase
    - Constrain the optical flow equation
    - Minimize SSD between the current frame and the motion compensated previous frame
- Deep learning approaches
  - CNN
  - FlowNet

## Object tracking

- Object detection: Localize (draw bounding box) + classify objects in an image
- Object tracking: Follow uniquely identified objects in a video
(more often indicated by moving bounding boxes with IDs)
  - Single object
  - Multiple object
- Challenges in illumination, scale, appearance, occultation and clutter, camera motion, data representation suited to the data variability
- Two building blocks:
  - Appearance model: how the tracked object visuals are represented?
    - Mandatory, to locate the object and differentiate it from other objects and background
  - Motion model: how the tracked object moves over time?
    - Optional, allows to predict the future location of the object
    - Reduces the number of “identity switches” in multiple object detection
    - Prediction-correction of location implemented in Kalman filter and particle filter algorithms
- Appearance modeling
  - Simplest method: record pixel intensities in the patch, which can then be compared using sum-of-square differences
    - Not a good method
  - Generative approach: define an explicit representation/feature space for patches
  - Discriminative approach: appearance model is implicitly defined by a machine learning model
    - Object detection: machine learning model is trained offline
    - Data association: candidate objects in the current frame are subsequently associated with a track based on their proximity to tracked object bounding boxes in previous frames
- Motion modeling
  - Incorporate dynamics which are used to predict the future location of the object based on its current location, before even seeing the next image
    - Do less looking for the object, get improved estimates
    - Assumes continuous motion patterns
  - Simple motion models: constant velocity, constant acceleration (with noise)
- Appearance model interpreted as a probabilistic observation model
  - Discriminative approach $p(z_t|x_t)=p_\text{noise}(z_t-Mx_t)$
  - Generative approach $p(z_t|x_t)\propto\exp(-\lambda d^2(x_t, y_t))$
- Bayesian estimation $p(x_k|x_{k-1})$, $p(z_t|x_t)$
  - Goal $p(x_k|z_{1:k})$ from $p(x_{k-1}|z_{1:k-1})$
    - Initialized with prior $p(x_0|z_{1:0}):=p(x_0)$
- Hidden Markov Model: $p(x_0,\dots, x_k, z_1, \dots, z_k)=p(x_0)\prod\limits_{i=1}kp(z_i|x_i)p(x_i|x_{i-1})$
  - The current state depends only on the previous state
  - Observations are independent conditionally to the states, and the current observation only depends on the current state
  - Predict and update steps
- Kalman filtering
  - State transition model: $x_k:=F_kx_{k-1}+w_k$, $w_k$ process noise
  - Observation model: $z_k:=K_kx_k+v_k$, $v_k$ observation noise
- Tracking by detection: SORT/DeepSORT
- Color based probabilistic tracking: HSV histograms, H and S components
- Particle filtering: approximate a distribution by a set of weighted samples
  - Sequential Importance Sampling (SIS)
  - Sequential Importance Resampling (SIR): same as SIS with a resampling step to avoid degeneracy of the samples (all but one particle with non negligible weight)
    - Resampling when number of effective sample size is less than a threshold

## Projective geometry and calibration

- Homography $H$
  - Is non singular
  - Is an *homogeneous* matrix, since only the ratios of its coefficients matter
  - Has $8$ dof
    - Thus it is possible to compute $H$ from 4 point correspondances, with no 3 of them colinear on a plane
- Affine transformation
  - $H_A$ has 6 dof and can thus be estimated using $3$ points correspondances
  - Preserved properties: parallel lines, ratios of lengths of parallel line segments, ratios of areas
- Similarities
- Isometries
- DLT
- RANSAC: SIFT keypoints

## Calibration

- Camera calibration matrix
- Radial distortion: barrel, pincushion
  - Modeled with a polynomial model
- Tangential distortion can be modeled by adding a perturbation to $x_r$
