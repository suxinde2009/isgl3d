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

#import "Isgl3dGLUIImage.h"
#import "Isgl3dPlane.h"
#import "Isgl3dTextureMaterial.h"
#import "Isgl3dUVMap.h"

@implementation Isgl3dGLUIImage



- (id) initWithMaterial:(Isgl3dMaterial *)material width:(unsigned int)width height:(unsigned int)height {
	
	if ((self = [super initWithMesh:[[[Isgl3dPlane alloc] initWithGeometry:width height:height nx:2 ny:2] autorelease] andMaterial:material])) {
		[self setWidth:width andHeight:height];
	}
	
	return self;	
}

- (id) initWithMaterial:(Isgl3dMaterial *)material andRectangle:(CGRect)rectangle width:(unsigned int)width height:(unsigned int)height {
	if ([material isKindOfClass:[Isgl3dTextureMaterial class]]) {
		Isgl3dTextureMaterial * textureMaterial = (Isgl3dTextureMaterial *)material;
		float materialWidth = textureMaterial.width;
		float materialHeight = textureMaterial.height;
		
		CGPoint origin = rectangle.origin;
		CGSize size = rectangle.size;
		
		float ua = origin.x / materialWidth;
		float va = origin.y / materialHeight;
		
		float ub = ua + size.width / materialWidth;
		float vb = va;

		float uc = ua;
		float vc = va + size.height / materialHeight;
		
		if ((self = [super initWithMesh:[[[Isgl3dPlane alloc] initWithGeometryAndUVMap:width height:height nx:2 ny:2 uvMap:[Isgl3dUVMap uvMapWithUA:ua vA:va uB:ub vB:vb uC:uc vC:vc]] autorelease] andMaterial:material])) {
			[self setWidth:width andHeight:height];
		}
		
		return self;	

	}
	
	return [self initWithMaterial:material width:width height:height];
	
}

- (void) dealloc {
	
	[super dealloc];
}

@end
