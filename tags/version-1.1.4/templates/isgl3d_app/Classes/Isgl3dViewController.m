//
//  Isgl3dViewController.m
//  ___PROJECTNAME___
//
//  Created by ___FULLUSERNAME___ on ___DATE___.
//  Copyright ___ORGANIZATIONNAME___ ___YEAR___. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>

#import "Isgl3dViewController.h"
#import "Isgl3dView3D.h"

@implementation Isgl3dViewController

@synthesize animating;

- (id) initWithNibName:(NSString *)nibName bundle:(NSBundle *)bundle {
	if ((self = [super initWithNibName:nibName bundle:bundle])) {
	
	    animating = FALSE;
	    displayLinkSupported = FALSE;
	    animationFrameInterval = 1;
	    displayLink = nil;
	    animationTimer = nil;
	    
	    // Use of CADisplayLink requires iOS version 3.1 or greater.
		// The NSTimer object is used as fallback when it isn't available.
	    NSString *reqSysVer = @"3.1";
	    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
	    if ([currSysVer compare:reqSysVer options:NSNumericSearch] != NSOrderedAscending) {
	        displayLinkSupported = TRUE;
	    }		
	}
	
	return self;
}

- (void)dealloc {    
    [super dealloc];
}

- (void)viewWillAppear:(BOOL)animated {
    [self startAnimation];
    
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated {
    [self stopAnimation];
    
    [super viewWillDisappear:animated];
}

- (void)viewDidUnload {
	[super viewDidUnload];
}

- (NSInteger)animationFrameInterval {
    return animationFrameInterval;
}

- (void)setAnimationFrameInterval:(NSInteger)frameInterval {
    /*
	 Frame interval defines how many display frames must pass between each time the display link fires.
	 The display link will only fire 30 times a second when the frame internal is two on a display that refreshes 60 times a second. The default frame interval setting of one will fire 60 times a second when the display refreshes at 60 times a second. A frame interval setting of less than one results in undefined behavior.
	 */
    if (frameInterval >= 1) {
        animationFrameInterval = frameInterval;
        
        if (animating) {
            [self stopAnimation];
            [self startAnimation];
        }
    }
}

- (void)startAnimation {
    if (!animating) {
        if (displayLinkSupported) {
            /*
			 CADisplayLink is API new in iOS 3.1. Compiling against earlier versions will result in a warning, but can be dismissed if the system version runtime check for CADisplayLink exists in -awakeFromNib. The runtime check ensures this code will not be called in system versions earlier than 3.1.
            */
            displayLink = [NSClassFromString(@"CADisplayLink") displayLinkWithTarget:self selector:@selector(drawFrame)];
            [displayLink setFrameInterval:animationFrameInterval];
            
            // The run loop will retain the display link on add.
            [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
        } else {
            animationTimer = [NSTimer scheduledTimerWithTimeInterval:(NSTimeInterval)((1.0 / 60.0) * animationFrameInterval) target:self selector:@selector(drawFrame) userInfo:nil repeats:TRUE];
		}
        
        animating = TRUE;
    }
}

- (void)stopAnimation {
    if (animating) {
        if (displayLinkSupported) {
            [displayLink invalidate];
            displayLink = nil;
        } else {
            [animationTimer invalidate];
            animationTimer = nil;
        }
        
        animating = FALSE;
    }
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}

- (void) drawFrame {
	[(Isgl3dView3D *)self.view drawView];
}

@end