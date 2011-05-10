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

#import "PrimitivesDemoView.h"
#import "Isgl3dDemoCameraController.h"

@implementation PrimitivesDemoView

- (id) init {
	
	if ((self = [super init])) {
		// Create and configure touch-screen camera controller
		_cameraController = [[Isgl3dDemoCameraController alloc] initWithCamera:self.camera andView:self];
		_cameraController.orbit = 17;
		_cameraController.theta = 30;
		_cameraController.phi = 10;
		_cameraController.doubleTapEnabled = NO;

		_container = [[self.scene createNode] retain];
		
		// Create the primitive
		Isgl3dTextureMaterial * material = [Isgl3dTextureMaterial materialWithTextureFile:@"red_checker.png" shininess:0.9 precision:Isgl3dTexturePrecisionMedium repeatX:NO repeatY:NO];
	
		Isgl3dTorus * torusMesh = [Isgl3dTorus meshWithGeometry:2 tubeRadius:1 ns:32 nt:32];
		_torus = [_container createNodeWithMesh:torusMesh andMaterial:material];
		[_torus setTranslation:-7 y:0 z:0];
	
		Isgl3dCone * coneMesh = [Isgl3dCone meshWithGeometry:4 topRadius:0 bottomRadius:2 ns:32 nt:32 openEnded:NO];
		_cone = [_container createNodeWithMesh:coneMesh andMaterial:material];
		[_cone setTranslation:7 y:0 z:0];
	
		Isgl3dCylinder * cylinderMesh = [Isgl3dCylinder meshWithGeometry:4 radius:1 ns:32 nt:32 openEnded:NO];
		_cylinder = [_container createNodeWithMesh:cylinderMesh andMaterial:material];
		[_cylinder setTranslation:0 y:0 z:-7];
	
		Isgl3dArrow * arrowMesh = [Isgl3dArrow meshWithGeometry:4 radius:0.4 headHeight:1 headRadius:0.6 ns:32 nt:32];
		_arrow = [_container createNodeWithMesh:arrowMesh andMaterial:material];
		[_arrow setTranslation:0 y:0 z:7];
		
		Isgl3dOvoid * ovoidMesh = [Isgl3dOvoid meshWithGeometry:1.5 b:2 k:0.2 longs:32 lats:32];
		_ovoid = [_container createNodeWithMesh:ovoidMesh andMaterial:material];
		[_ovoid setTranslation:0 y:-4 z:0];
		
		Isgl3dGoursatSurface * gouratMesh = [Isgl3dGoursatSurface meshWithGeometry:0 b:0 c:-1 width:2 height:3 depth:2 longs:8 lats:16];
		_gourat = [_container createNodeWithMesh:gouratMesh andMaterial:material];
		[_gourat setTranslation:0 y:4 z:0];
		
		// Add light
		Isgl3dLight * light  = [Isgl3dLight lightWithHexColor:@"FFFFFF" diffuseColor:@"FFFFFF" specularColor:@"FFFFFF" attenuation:0.005];
		[light setTranslation:5 y:15 z:15];
		[self.scene addChild:light];
		
		// Schedule updates
		[self schedule:@selector(tick:)];
	}
	
	return self;
}

- (void) dealloc {
	[_cameraController release];

	[super dealloc];
}

- (void) onActivated {
	// Add camera controller to touch-screen manager
	[[Isgl3dTouchScreen sharedInstance] addResponder:_cameraController];
}

- (void) onDeactivated {
	// Remove camera controller from touch-screen manager
	[[Isgl3dTouchScreen sharedInstance] removeResponder:_cameraController];
}

- (void) tick:(float)dt {
	_containerRotation += 0.2;
	
	[_container setRotation:_containerRotation x:0 y:1 z:0];
	[_torus setRotation:_containerRotation x:0 y:1 z:0];
	[_cone setRotation:_containerRotation * 2 x:0 y:1 z:0];
	[_cylinder setRotation:-_containerRotation * 3 x:0 y:1 z:0];
	[_arrow setRotation:-_containerRotation * 6 x:0 y:1 z:0];
	[_gourat setRotation:-_containerRotation * 2 x:0 y:1 z:0];
	
	// update camera
	[_cameraController update];
}


@end



#pragma mark AppDelegate

/*
 * Implement principal class: simply override the createViews method to return the desired demo view.
 */
@implementation AppDelegate

- (void) createViews {
	// Set the device orientation
	[Isgl3dDirector sharedInstance].deviceOrientation = Isgl3dOrientationLandscapeLeft;

	// Create view and add to Isgl3dDirector
	Isgl3dView * view = [PrimitivesDemoView view];
	[[Isgl3dDirector sharedInstance] addView:view];
}

@end