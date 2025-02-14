//
//  SBKeyboardManager.h
//  YYKit <https://github.com/ibireme/YYKit>
//
//  Created by ibireme on 15/6/3.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

#if __has_include(<SBKeyboardManager/SBKeyboardManager.h>)
FOUNDATION_EXPORT double SBKeyboardManagerVersionNumber;
FOUNDATION_EXPORT const unsigned char SBKeyboardManagerVersionString[];
#endif

NS_ASSUME_NONNULL_BEGIN

/**
 System keyboard transition information.
 Use -[SBKeyboardManager convertRect:toView:] to convert frame to specified view.
 */
typedef struct {
    BOOL fromVisible; ///< Keyboard visible before transition.
    BOOL toVisible;   ///< Keyboard visible after transition.
    CGRect fromFrame; ///< Keyboard frame before transition.
    CGRect toFrame;   ///< Keyboard frame after transition.
    NSTimeInterval animationDuration;       ///< Keyboard transition animation duration.
    UIViewAnimationCurve animationCurve;    ///< Keyboard transition animation curve.
    UIViewAnimationOptions animationOption; ///< Keybaord transition animation option.
} SBKeyboardTransition;


/**
 The SBKeyboardObserver protocol defines the method you can use
 to receive system keyboard change information.
 */
@protocol SBKeyboardObserver <NSObject>
@optional
- (void)keyboardChangedWithTransition:(SBKeyboardTransition)transition;
@end


/**
 A SBKeyboardManager object lets you get the system keyboard information,
 and track the keyboard visible/frame/transition.
 
 @discussion You should access this class in main thread.
 Compatible: iPhone/iPad with iOS6/7/8/9.
 */
@interface SBKeyboardManager : NSObject

- (instancetype)init UNAVAILABLE_ATTRIBUTE;
+ (instancetype)new UNAVAILABLE_ATTRIBUTE;

/// Get the default manager.
+ (instancetype)defaultManager;

/// Get the keyboard window. nil if there's no keyboard window.
@property (nullable, nonatomic, readonly) UIWindow *keyboardWindow;

/// Get the keyboard view. nil if there's no keyboard view.
@property (nullable, nonatomic, readonly) UIView *keyboardView;

/// Whether the keyboard is visible.
@property (nonatomic, readonly, getter=isKeyboardVisible) BOOL keyboardVisible;

/// Get the keyboard frame. CGRectNull if there's no keyboard view.
/// Use convertRect:toView: to convert frame to specified view.
@property (nonatomic, readonly) CGRect keyboardFrame;


/**
 Add an observer to manager to get keyboard change information.
 This method makes a weak reference to the observer.
 
 @param observer An observer.
 This method will do nothing if the observer is nil, or already added.
 */
- (void)addObserver:(id<SBKeyboardObserver>)observer;

/**
 Remove an observer from manager.
 
 @param observer An observer.
 This method will do nothing if the observer is nil, or not in manager.
 */
- (void)removeObserver:(id<SBKeyboardObserver>)observer;

/**
 Convert rect to specified view or window.
 
 @param rect The frame rect.
 @param view A specified view or window (pass nil to convert for main window).
 @return The converted rect in specifeid view.
 */
- (CGRect)convertRect:(CGRect)rect toView:(nullable UIView *)view;

@end

NS_ASSUME_NONNULL_END
