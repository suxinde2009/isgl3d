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
#import <CoreGraphics/CoreGraphics.h>
#import "Isgl3dTouchScreenResponder.h"

@class Isgl3dView3D;
@class UITouch;

/**
 * The Isgl3dTouchScreen provides a singleton class that delegates all touch events that occur on the device display.
 * 
 * This provides additional functionality to the events that occur on the rendered objects (the Isgl3dEvent3D): these touch
 * events are intended to be handled directly by the application using iSGL3D rather than iSGL3D itself.
 * 
 * Touch events are forwarded here from the Isgl3dGLView3D (which inherits from UIView): the standard UIResponder methods
 * for touches are therefore available.
 * 
 * When using the Isgl3dTouchScreen, a call to setupWithView must be made during the initialisation of the application.
 */
@interface Isgl3dTouchScreen : NSObject  {
	Isgl3dView3D * _view;
	
	NSMutableArray * _responders;
}


/**
 * Returns the singleton instance of the Isgl3dTouchScreen.
 * @return singleton instance The instance of the Isgl3dTouchScreen.
 */
+ (Isgl3dTouchScreen *) sharedInstance;

/**
 * Resets the singleton instance. All Isgl3dTouchScreenResponders are removed and need to be added again. Also a call to setupWithView:
 * must be made again.
 */
+ (void) resetInstance;

/**
 * Initialises the Isgl3dTouchScreen withe the Isgl3dView3D.
 * @param view the Isgl3dView3D.
 */
- (void) setupWithView:(Isgl3dView3D *)view;

/*
 * Adds a new object that implements the Isgl3dTouchScreenResponder protocol to the array of responders. All touch events
 * will subsequently be forwarded to this object.
 * @param responder An object implementing the Isgl3dTouchScreenResponder protocol to which touch events should be forwarded.
 */
- (void) addResponder:(id <Isgl3dTouchScreenResponder>)responder;

/**
 * Removes a particular object that implements the Isgl3dTouchScreenResponder protocol from the array of responders.
 * Note: it is very important that an object implementing this protocol does not try to remove itself from the Isgl3dTouchScreen
 * during its dealloc method: the Isgl3dTouchScreen stores the object in an array and therefore increases the retain count on the object. For
 * this reason, the dealloc method of the object will never be called and hence a memory leak is possible.
 * @param responder An object implementing the Isgl3dTouchScreenResponder protocol that should be removed from the array of responders.
 */
- (void) removeResponder:(id <Isgl3dTouchScreenResponder>)responder;

/**
 * Tells the receiver when one or more fingers touch down in a view or window.
 * @param touches A set of UITouch instances that represent the touches for the starting phase of the event represented by event.
 * @param event An object representing the event to which the touches belong.
 */
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;

/**
 * Tells the receiver when one or more fingers associated with an event move within a view or window.
 * @param touches A set of UITouch instances that represent the touches that are moving during the event represented by event.
 * @param event An object representing the event to which the touches belong.
 */
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;

/**
 * Tells the receiver when one or more fingers are raised from a view or window.
 * @param touches A set of UITouch instances that represent the touches for the ending phase of the event represented by event.
 * @param event An object representing the event to which the touches belong.
 */
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;

/**
 * Returns the location in the view for a particular UITouch.
 * @param touch The UITouch.
 * @return the location on the display as a CGPoint.
 */
- (CGPoint) locationInView:(UITouch *)touch;

@end