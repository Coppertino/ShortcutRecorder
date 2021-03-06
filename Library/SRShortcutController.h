//
//  SRShortcutController.h
//  ShortcutRecorder.framework
//
//  Copyright 2018 Contributors. All rights reserved.
//  License: BSD
//
//  Contributors to this file:
//      Ilya Kulakov

#import <Cocoa/Cocoa.h>

#import<ShortcutRecorder/SRRecorderControl.h>
#import <ShortcutRecorder/SRShortcut.h>


NS_ASSUME_NONNULL_BEGIN

/*!
    Keys for the computed properties of controller's selection.
 */
typedef NSString *SRShortcutControllerSelectionKey NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(ShortcutControllerSelectionKey);
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeyKeyEquivalent;
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeyKeyEquivalentModifierMask;
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeyLiteralKeyCode;
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeySymbolicKeyCode;
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeyLiteralASCIIKeyCode;
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeySymbolicASCIIKeyCode;
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeyLiteralModifierFlags;
extern SRShortcutControllerSelectionKey const SRShortcutControllerSelectionKeySymbolicModifierFlags;


/*!
    Key paths for the computed properties of the controller.
 */
typedef NSString *SRShortcutControllerKeyPath NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(ShortcutControllerKeyPath);
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathKeyEquivalent;
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathKeyEquivalentModifierMask;
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathLiteralKeyCode;
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathSymbolicKeyCode;
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathLiteralASCIIKeyCode;
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathSymbolicASCIIKeyCode;
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathLiteralModifierFlags;
extern SRShortcutControllerKeyPath const SRShortcutControllerKeyPathSymbolicModifierFlags;

/*!
    Implementation of NSObjectController with additional computed properties.

    @discussion In addition to providing the common benefits of using NSObjectController over a plain model,
                it implements the following computed properties:
                    - selection.keyEquivalent
                    - selection.keyEquivalentModifierMask
                    - selection.literalKeyCode
                    - selection.symbolicKeyCode
                    - selection.literalASCIIKeyCode
                    - selection.symbolicASCIIKeyCode
                    - selection.literalModifierFlags
                    - selection.symbolicModifierFlags

                These properties are KVO compliant.
                The following properties are also updated whenever kTISNotifySelectedKeyboardInputSourceChanged is posted:
                    - selection.keyEquivalent
                    - selection.literalKeyCode
                    - selection.symbolicKeyCode
                    - selection.literalASCIIKeyCode
                    - selection.selection.symbolicASCIIKeyCode

    @note To add the controller in Interface Builder, add NSObjectController first and then specialize its class.
 */
NS_SWIFT_NAME(ShortcutController)
@interface SRShortcutController : NSObjectController

@property (nullable, strong) SRShortcut *content;

- (instancetype)initWithContent:(nullable SRShortcut *)aContent;
- (void)addObject:(SRShortcut *)anObject;
- (void)removeObject:(SRShortcut *)anObject;

- (void)addSelectedKeyboardInputSourceObserverIfNeeded;
- (void)removeSelectedKeyboardInputSourceObserverIfNeeded;
- (void)onSelectedKeyboardInputSourceObserverChange;
- (void)updateComputedKeyPaths;

@end


@interface SRShortcutController (/* IBDesignable */) /* <NSNibLoading> */

/*!
    Recorder control to bind when loading from NIB.

    @discussion Controller will bind Control's NSValueBinding to the same source as its own NSContentObjectBinding
                by using the same transformers (usually NSKeyedUnarchiveFromData).
                As a result changes made via the Control will be propagated to the Model and therefore
                observed by the Controller and its own subscribers further down the chain.

    @note Only meaningful when instances of SRShortcutController created inside Interface Builder files.
 */
@property (weak) IBOutlet SRRecorderControl *control;

@end

NS_ASSUME_NONNULL_END
