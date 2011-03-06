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

#include "Isgl3dMiniVec.h"
#import "Isgl3dCamera.h"

/**
 * The Isgl3dSpringCamera is similar to the Isgl3dFollowCamera in that it is used to automatically
 * move a camera as a target node moves. However, unlike the Isgl3dFollowCamera, it follows the
 * full transformation (position and rotation) of the target rather than its position and movement.
 * 
 * The Isgl3dSpringCamera can be thought of as being attached to the target at a specific desired
 * location relative to the target's local coordinate system. The movement of the camera is such
 * that it appears to be attached via a spring and has damping dependent on its velocity.
 * 
 * By modifying the stiffness of the spring, the amount of damping and its mass, the
 * behaviour of the camera as the target moves can be modified.
 * 
 * As well as a desired position relative to the target, a look-at position (also relative to the  
 * target) can be specified.
 */
@interface Isgl3dSpringCamera : Isgl3dCamera {
	    
@private
	Isgl3dNode * _target;

	//Matrix4D * _targetTransformation;

	Isgl3dMiniVec3D _positionOffset;
	Isgl3dMiniVec3D _lookOffset;
	Isgl3dMiniVec3D _velocity;

	Isgl3dMiniVec3D _desiredPosition;
	Isgl3dMiniVec3D _desiredLookAtPosition;
	Isgl3dMiniVec3D _acceleration;


	float _stiffness;
	float _damping;
	float _mass;
	
	BOOL _initialized;
	BOOL _useRealTime;
	NSDate * _time;
}

/**
 * Specifies the desired position of camera relative to the target. 
 */
@property (nonatomic) Isgl3dMiniVec3D positionOffset;

/**
 * Specifies the camera look-at position relative to the target. 
 */
@property (nonatomic) Isgl3dMiniVec3D lookOffset;

/**
 * Modifies the stiffness of the spring. By default this is 10.
 */
@property (nonatomic) float stiffness;

/**
 * Modifies the amount of damping. By default this is 4.
 */
@property (nonatomic) float damping;

/**
 * Modifies the mass of the camera. By default this is 1.
 */
@property (nonatomic) float mass;

/**
 * Returns the target node.
 */
@property (readonly) Isgl3dNode * target;

/**
 * Uses real time to calculate the changes in position and the resulting acceleration on the camera.
 * This can produce adverse effects if low frame rates are encountered. If not using real time, a delay 
 * of 1/60s is assumed.
 */
@property (nonatomic) BOOL useRealTime;

/**
 * Initialises the Isgl3dSpringCamera with an Isgl3dView3D object and the target node.
 * @param view3D The Isgl3dView3D in use.
 * @param target The target node.
 */
- (id) initWithView:(Isgl3dView3D *)view3D andTarget:(Isgl3dNode *)target;

/**
 * Sets the target to a different Isgl3dNode.
 * @param target The target node.
 */
- (void) setTarget:(Isgl3dNode *)target;

@end