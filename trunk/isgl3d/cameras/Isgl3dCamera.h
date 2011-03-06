/*
 * iSGL3D: http://isgl3d.com
 *
 * Copyright (c) 2010-2011 Stuart Caunt
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#import "Isgl3dNode.h"

@class Isgl3dMatrix4D;
@class Isgl3dView3D;

/**
 * The Isgl3dCamera is the principal form of camera used in iSGL3D. It behaves as a traditional camera and is 
 * used to provide a projection of the scene as viewed from an observer.
 * 
 * Two transformation matrices are contained in the camera: the view matrix which represents the position and orientation
 * of the camera, and the projection matrix which describes how the scene should be projected (either as perspective or
 * orthographic).
 * 
 * The Isgl3dCamera inherits all the essential transformations relating to all Isgl3dGLObjects. This means that a camera
 * can be translation and rotated and the rendered scene changes automatically.
 * 
 * As well as the camera's position and rotation, it has two elements that are important: the <em>look-at</em> and the
 * <em>up vector</em>. The look-at represents a point in space that lies direcly along the camera's z-axis (direction of
 * view of the observer). The up vector represents the y-axis of the camera: the x-axis is automatically calculated
 * as the cross product of these two.
 * 
 * The camera also has certain properties to modify the rendering depending on the type or projection used. For
 * perspective projections we have the following:
 * <ul>
 *   <li>Field of view: this is the angle between the z-axis of the camera and the maximum vertical angle visible.</li>
 *   <li>Aspect ratio: this defines the ratio between the maximum horizontal angle and the maximum vertical angle.</li>
 *   <li>Focus: The focus is sometimes the hardest to understand. It is related to the field of view and the width
 * and height (in pixels) of the view. It represents the distance to an object with the same dimensions as the view would 
 * be if it fully occupied the display.</li>
 *   <li>Zoom: modifying the zoom modifies the visible size of the objects in the scene. With a zoom of 2 objects
 * will appear twice as big.</li>
 *   <li>The near and far value: these correspond the minimum and maximum distances to objects to be rendered. Objects 
 * closer than the near or further from the far are not rendered.</li> 
 * </ul>
 * 
 * For orthographic projections the following properties are important:
 * <ul>
 *   <li>left and right values: The minimum and maximum distances along the x-axis within which objects are rendered.</li>
 *   <li>bottom and top values: The minimum and maximum distances along the y-axis within which objects are rendered.</li>
 *   <li>near and far values: The minimum and maximum distances to objects to be rendered.</li>
 * </ul>
 * 
 * The above values are of course relative the the x, y and z-values as they appear to the camera and not physically in
 * world-space. 
 * 
 * It is necessary to indicate whether the camera is in landscape of portrait mode: For an application intended to be used 
 * with an iPhone in landscape orientation, the camera too should be in landscape mode.
 * 
 * The Isgl3dCamera inherits from Isgl3dNode so that, if desired, it can be rendered on the scene (for example if multiple
 * cameras are in use, one of the cameras may be visible to the other). This can be achieved by adding an Isgl3dMesh node 
 * directly as a child.
 */
@interface Isgl3dCamera : Isgl3dNode {
	    
@private
	Isgl3dMatrix4D * _viewMatrix;
	Isgl3dMatrix4D * _projectionMatrix;
	
	Isgl3dMiniVec3D _lookAt;
	
	float _upX;
	float _upY;
	float _upZ;
	
	Isgl3dMiniVec3D _initialCameraPosition;
	Isgl3dMiniVec3D _initialCameraLookAt;
	
	/**
	 * Vector used for temporary internal calculations.
	 */
	Isgl3dMiniVec3D _tempVector;
	
	float _fov;
	float _aspect;
	float _near;
	float _far;
	BOOL _isPerspective;
	float _left;
	float _right;
	float _bottom;
	float _top;
	BOOL _isLandscape;

	float _width;	
	float _height;	
	float _focus;
	float _zoom;
	
	Isgl3dMiniVec3D _cameraPosition;
}

/**
 * The initial position of the camera as defined during its initialisation or set afterwards.
 * A call to reset on the camera will place the camera at this position.
 */
@property (nonatomic) Isgl3dMiniVec3D initialCameraPosition;

/**
 * The initial look-at position of the camera as defined during its initialistion or set afterwards. 
 * A call to reset on the camera will make the camera look-at this position.
 */
@property (nonatomic) Isgl3dMiniVec3D initialCameraLookAt;

/**
 * The current view matrix.
 */
@property (readonly) Isgl3dMatrix4D * viewMatrix;

/**
 * The current projection matrix.
 */
@property (readonly) Isgl3dMatrix4D * projectionMatrix;

/**
 * Indicates whether the camera is in perspective mode.
 */
@property (nonatomic) BOOL isPerspective;

/**
 * The field of view of the camera in degrees (in perspective mode).
 * This is the angle between the z-axis of the camera and the maximum vertical angle visible.
 */
@property (nonatomic) float fov;

/**
 * The aspect ratio of the camera (in perspective mode).
 * This defines the ratio between the maximum horizontal angle and the maximum vertical angle.
 */
@property (nonatomic) float aspect;

/**
 * The near value of the camera.
 * Objects closer than this value will not be rendered.
 */
@property (nonatomic) float near;

/**
 * The far value of the camera.
 * Objects further than this value will not be rendered.
 */
@property (nonatomic) float far;

/**
 * The left value of the camera (in orthographic mode).
 * Objects further to the left (along the x-axis) than this value will not be rendered.
 */
@property (nonatomic) float left;

/**
 * The right value of the camera (in orthographic mode).
 * Objects further to the right (along the x-axis) than this value will not be rendered.
 */
@property (nonatomic) float right;

/**
 * The bottom value of the camera (in orthographic mode).
 * Objects below this (along the y-axis) than this value will not be rendered.
 */
@property (nonatomic) float bottom;

/**
 * The top value of the camera (in orthographic mode).
 * Objects above this (along the y-axis) than this value will not be rendered.
 */
@property (nonatomic) float top;

/**
 * The focus of the camera (in perspective mode).
 * This represents the distance to an object with the same dimensions as the view (in terms of pixel width and height) would 
 * be if it fully occupied the display.
 */
@property (nonatomic) float focus;

/**
 * The zoom of the camera (in perspective mode).
 * This represents the amount of zooming of the camera so that objects appear closer or further away.
 */
@property (nonatomic) float zoom;

/*
 * Warning: should NEVER be called: this is here to produce a warning log message. An Isgl3DCamera should
 * ALWAYS be initialised with an Isgl3dView3D.
 */
- (id) init;

/**
 * Initialises the camera with an Isgl3dView3D object.
 * Default initialisation of the camera: The camera is position at (0, 0, 10) looking directly towards the origin
 * with its y-axis parallel to the world-space y-axis. Perspective projection is used as default.
 * @param view The view to be used by the camera (provides width and height).
 */
- (id) initWithView:(Isgl3dView3D *)view;

/**
 * Initialises the camera with a specified width and height.
 * Default initialisation of the camera: The camera is position at (0, 0, 10) looking directly towards the origin
 * with its y-axis parallel to the world-space y-axis. Perspective projection is used as default.
 * @param width The width of the view.
 * @param height The height of the view.
 */
- (id) initWithWidth:(float)width andHeight:(float)height;

/**
 * Initialises the camera with user-defined geometry.
 * Perspective projection is used as default.
 * @param view The view to be used by the camera (provides width and height).
 * @param x The x position of the camera.
 * @param y The y position of the camera.
 * @param z The z position of the camera.
 * @param upX The x component of the up vector.
 * @param upY The y component of the up vector.
 * @param upZ The z component of the up vector.
 * @param lookAtX The x position where the camera will look at.
 * @param lookAtY The y position where the camera will look at.
 * @param lookAtZ The z position where the camera will look at.
 */
- (id) initWithView:(Isgl3dView3D *)view andCoordinates:(float)x y:(float)y z:(float)z upX:(float)upX upY:(float)upY upZ:(float)upZ lookAtX:(float)lookAtX lookAtY:(float)lookAtY lookAtZ:(float)lookAtZ;

/**
 * Initialises the camera with user-defined geometry.
 * Perspective projection is used as default.
 * @param width The width of the view.
 * @param height The height of the view.
 * @param x The x position of the camera.
 * @param y The y position of the camera.
 * @param z The z position of the camera.
 * @param upX The x component of the up vector.
 * @param upY The y component of the up vector.
 * @param upZ The z component of the up vector.
 * @param lookAtX The x position where the camera will look at.
 * @param lookAtY The y position where the camera will look at.
 * @param lookAtZ The z position where the camera will look at.
 */
- (id) initWithWidth:(float)width height:(float)height andCoordinates:(float)x y:(float)y z:(float)z upX:(float)upX upY:(float)upY upZ:(float)upZ lookAtX:(float)lookAtX lookAtY:(float)lookAtY lookAtZ:(float)lookAtZ;


/**
 * Resets the camera position and look-at to their initial values.
 */
- (void) reset;

/**
 * Sets the camera in projective projection mode with the given parameters.
 * @param fovy The field of view in the y direction.
 * @param near The near value (closer than this an objects won't be rendered).
 * @param far The far value (further than this an objects won't be rendered).
 * @landscape Indicates whether the camera should assume that the device is oriented in landscape mode.
 */
- (void) setPerspectiveProjection:(float)fovy near:(float)near far:(float)far landscape:(BOOL)landscape;

/**
 * Sets the camera in orthographics projection mode.
 * @param left The left value (Objects to the left of this won't be rendered).
 * @param right The right value (Objects to the right of this won't be rendered).
 * @param bottom The bottom value (Objects below this won't be rendered).
 * @param top The top value (Objects above this won't be rendered).
 * @param near The near value (closer than this an objects won't be rendered).
 * @param far The far value (further than this an objects won't be rendered).
 * @landscape Indicates whether the camera should assume that the device is oriented in landscape mode.
 */
- (void) setOrthoProjection:(float)left right:(float)right bottom:(float)bottom top:(float)top near:(float)near far:(float)far landscape:(BOOL)landscape;

/**
 * Specifies the postion in space as a vector where the camera should look at.
 * param lookAt The vector containing the look-at position.
 */
- (void) setLookAt:(Isgl3dMiniVec3D *)lookAt;

/**
 * Specifies the postion in space as separated components where the camera should look at.
 * param x The x position of the look-at position.
 * param y The y position of the look-at position.
 * param z The z position of the look-at position.
 */
- (void) lookAt:(float)x y:(float)y z:(float)z;

/**
 * Used to obtain the look-at position as a vector.
 * The Isgl3dMiniVec3D object is modified to contain the coordinates of the current look-at. 
 */
- (void) getLookAt:(Isgl3dMiniVec3D *)lookAt;

/**
 * Used to obtain the vector along the direction of view from the observer's position.
 * The Isgl3dMiniVec3D object is modified to contain the vector along the direction of view (in essence the
 * current look-at position minus the camera position). 
 */
- (void) getEyeNormal:(Isgl3dMiniVec3D *)eyeNormal;

/**
 * Returns the x component of the look-at position.
 * @return the x component of the look-at position.
 */
- (float) getLookAtX;

/**
 * Returns the y component of the look-at position.
 * @return the y component of the look-at position.
 */
- (float) getLookAtY;

/**
 * Returns the z component of the look-at position.
 * @return the z component of the look-at position.
 */
- (float) getLookAtZ;

/**
 * Translates the current look at.
 * @param x The distance along the x-axis to move the look-at
 * @param y The distance along the y-axis to move the look-at
 * @param z The distance along the z-axis to move the look-at
 */
- (void) translateLookAt:(float)x y:(float)y z:(float)z;

/**
 * Performs a rotation of the look-at position about the x-axis centered on a specific point on the y-z plane.
 * @param angle The angle of rotation in degrees.
 * @param centerY The position y on the y-z plane.
 * @param centerZ The position z on the y-z plane.
 */
- (void) rotateLookAtOnX:(float)angle centerY:(float)centerY centerZ:(float)centerZ;

/**
 * Performs a rotation of the look-at position about the y-axis centered on a specific point on the x-z plane.
 * @param angle The angle of rotation in degrees.
 * @param centerX The position x on the x-z plane.
 * @param centerZ The position z on the x-z plane.
 */
- (void) rotateLookAtOnY:(float)angle centerX:(float)centerX centerZ:(float)centerZ;

/**
 * Performs a rotation of the look-at position about the z-axis centered on a specific point on the x-y plane.
 * @param angle The angle of rotation in degrees.
 * @param centerX The position x on the x-z plane.
 * @param centerY The position y on the y-z plane.
 */
- (void) rotateLookAtOnZ:(float)angle centerX:(float)centerX centerY:(float)centerY;

/**
 * Returns the distance from the camera's location to the look-at position.
 * @return The distance from the camera's location to the look-at position.
 */
- (float) getDistanceToLookAt;

/**
 * Sets the distance between the look-at position and the camera's location.
 * The look-at position remains fixed and the camera's position changes accordingly. This
 * can be useful for example if the look-at is set to the position of another object on the
 * scene and you wish to move the camera further away or closer to the object. 
 * @param distance The desired distance between the look at and the camera.
 */
- (void) setDistanceToLookAt:(float)distance;

/**
 * Sets the components of the up vector.
 * @param x The x component of the up vector.
 * @param y The y component of the up vector.
 * @param z The z component of the up vector.
 */
- (void) setUpX:(float)x y:(float)y z:(float)z;

@end
