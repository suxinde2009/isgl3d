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
#import "isgl3dTypes.h"

@class Isgl3dGLDepthRenderTexture;


/**
 * __isgl3d_internal__ Internal class of the iSGL3D framework
 */
@interface Isgl3dGLTextureFactoryState : NSObject {


}

- (id) init;

- (unsigned int) createTextureFromRawData:(void *)data width:(int)width height:(int)height mipmap:(BOOL)mipmap precision:(Isgl3dTexturePrecision)precision repeatX:(BOOL)repeatX repeatY:(BOOL)repeatY;
- (unsigned int) createTextureFromCompressedTexImageData:(NSArray *)imageData format:(unsigned int)format width:(uint32_t)width height:(uint32_t)height precision:(Isgl3dTexturePrecision)precision repeatX:(BOOL)repeatX repeatY:(BOOL)repeatY;
- (unsigned int) createCubemapTextureFromRawData:(void *)data width:(int)width mipmap:(BOOL)mipmap precision:(Isgl3dTexturePrecision)precision repeatX:(BOOL)repeatX repeatY:(BOOL)repeatY;
- (void) deleteTextureId:(unsigned int)textureId;
- (Isgl3dGLDepthRenderTexture *) createDepthRenderTexture:(int)width height:(int)height;
- (unsigned int) compressionFormatFromString:(NSString *)format;

@end
