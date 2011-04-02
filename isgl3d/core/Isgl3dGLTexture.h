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

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define GLTEXTURE_LOW_PRECISION 0
#define GLTEXTURE_MEDIUM_PRECISION 1
#define GLTEXTURE_HIGH_PRECISION 2

/**
 * __isgl3d_internal__ Internal class of the iSGL3D framework
 */
@interface Isgl3dGLTexture : NSObject {

@private
	unsigned int _textureId;
	
	unsigned int _width;
	unsigned int _height;
	CGSize _contentSize;
	
	BOOL _isHighDefinition;
}

- (id)initWithId:(unsigned int)textureId width:(unsigned int)width height:(unsigned int)height;
- (id)initWithId:(unsigned int)textureId width:(unsigned int)width height:(unsigned int)height contentSize:(CGSize)contentSize;

@property (nonatomic, readonly) unsigned int textureId;
@property (nonatomic, readonly) unsigned int width;
@property (nonatomic, readonly) unsigned int height;
@property (nonatomic, readonly) CGSize contentSize;
@property (nonatomic) BOOL isHighDefinition;

@end
