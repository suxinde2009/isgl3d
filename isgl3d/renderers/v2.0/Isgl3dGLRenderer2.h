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

#import <OpenGLES/ES2/gl.h>

#import "Isgl3dGLRenderer.h"

@class Isgl3dGLContext2;
@class Isgl3dMatrix4D;
@class Isgl3dGLRenderer2State;
@class Isgl3dShader;

/**
 * __isgl3d_internal__ Internal class of the iSGL3D framework
 */
@interface Isgl3dGLRenderer2 : Isgl3dGLRenderer {

@private
	Isgl3dGLContext2 * _glContext;

	Isgl3dMatrix4D * _mvpMatrix;
	Isgl3dMatrix4D * _mvMatrix;

	Isgl3dMatrix4D * _lightViewProjectionMatrix;
	Isgl3dMatrix4D * _lightModelViewProjectionMatrix;

	
	BOOL _shadowMapActive;

	unsigned int _currentVBOIndex;

	Isgl3dGLRenderer2State * _currentState;
	Isgl3dGLRenderer2State * _previousState;

	NSMutableDictionary * _shaders;
	Isgl3dShader * _activeShader;
	
	unsigned int _renderedObjects;

	GLuint _currentElementBufferId;
}

- (id) initWithContext:(Isgl3dGLContext2 *)context;

@end