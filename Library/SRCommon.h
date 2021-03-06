//
//  SRCommon.h
//  ShortcutRecorder
//
//  Copyright 2006-2018 Contributors. All rights reserved.
//
//  License: BSD
//
//  Contributors:
//      David Dauer
//      Jesper
//      Jamie Kirkpatrick
//      Andy Kim
//      Ilya Kulakov

#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>


NS_ASSUME_NONNULL_BEGIN

/*!
    Mask representing subset of Cocoa modifier flags suitable for shortcuts.
 */
static const NSEventModifierFlags SRCocoaModifierFlagsMask = NSEventModifierFlagCommand | NSEventModifierFlagOption | NSEventModifierFlagShift | NSEventModifierFlagControl;

/*!
    Mask representing subset of Carbon modifier flags suitable for shortcuts.
 */
static const NSUInteger SRCarbonModifierFlagsMask = cmdKey | optionKey | shiftKey | controlKey;


/*!
    These constants represents drawable unicode characters for key codes that do not have
    appropriate constants in Carbon and Cocoa.
 */
typedef NS_ENUM(unichar, SRKeyCodeGlyph)
{
    SRKeyCodeGlyphTabRight = 0x21E5, // ⇥
    SRKeyCodeGlyphTabLeft = 0x21E4, // ⇤
    SRKeyCodeGlyphReturn = 0x2305, // ⌅
    SRKeyCodeGlyphReturnR2L = 0x21A9, // ↩
    SRKeyCodeGlyphDeleteLeft = 0x232B, // ⌫
    SRKeyCodeGlyphDeleteRight = 0x2326, // ⌦
    SRKeyCodeGlyphPadClear = 0x2327, // ⌧
    SRKeyCodeGlyphLeftArrow = 0x2190, // ←
    SRKeyCodeGlyphRightArrow = 0x2192, // →
    SRKeyCodeGlyphUpArrow = 0x2191, // ↑
    SRKeyCodeGlyphDownArrow = 0x2193, // ↓
    SRKeyCodeGlyphPageDown = 0x21DF, // ⇟
    SRKeyCodeGlyphPageUp = 0x21DE, // ⇞
    SRKeyCodeGlyphNorthwestArrow = 0x2196, // ↖
    SRKeyCodeGlyphSoutheastArrow = 0x2198, // ↘
    SRKeyCodeGlyphEscape = 0x238B, // ⎋
    SRKeyCodeGlyphSpace = 0x0020, // ' '
};



/*!
    Convert Carbon modifier flags to Cocoa.
 */
NS_INLINE NSEventModifierFlags SRCarbonToCocoaFlags(UInt32 aCarbonFlags)
{
    NSEventModifierFlags cocoaFlags = 0;

    if (aCarbonFlags & cmdKey)
        cocoaFlags |= NSEventModifierFlagCommand;

    if (aCarbonFlags & optionKey)
        cocoaFlags |= NSEventModifierFlagOption;

    if (aCarbonFlags & controlKey)
        cocoaFlags |= NSEventModifierFlagControl;

    if (aCarbonFlags & shiftKey)
        cocoaFlags |= NSEventModifierFlagShift;

    return cocoaFlags;
}

/*!
    Convert Cocoa modifier flags to Carbon.
 */
NS_INLINE UInt32 SRCocoaToCarbonFlags(NSEventModifierFlags aCocoaFlags)
{
    UInt32 carbonFlags = 0;

    if (aCocoaFlags & NSEventModifierFlagCommand)
        carbonFlags |= cmdKey;

    if (aCocoaFlags & NSEventModifierFlagOption)
        carbonFlags |= optionKey;

    if (aCocoaFlags & NSEventModifierFlagControl)
        carbonFlags |= controlKey;

    if (aCocoaFlags & NSEventModifierFlagShift)
        carbonFlags |= shiftKey;

    return carbonFlags;
}


/*!
    Return Bundle where resources can be found.

    @throws NSInternalInconsistencyException

    @discussion Throws NSInternalInconsistencyException if bundle cannot be found.
*/
NSBundle * SRBundle(void);


/*!
    Convenience method to get localized string from the framework bundle.
 */
NSString * _Nullable SRLoc(NSString * _Nullable aKey);


/*!
    Convenience method to get image from the framework bundle.
 */
NSImage * _Nullable SRImage(NSString * _Nullable anImageName);


@interface NSObject (SRCommon)

/*!
 Uses -isEqual: of the most specialized class of the same hierarchy to maintain transitivity and associativity.

 In the root class that overrides -isEqual:

 - (BOOL)isEqualTo<Class>:(<Class> *)anObject
 {
     if (anObject == self)
         return YES;
     else if (![anObject isKindOfClass:<Class>.class])
         return NO;
     else
         return <memberwise comparison>;
 }

 - (BOOL)isEqual:(NSObject *)anObject
 {
     return [self SR_isEqual:anObject usingSelector:@selector(isEqualTo<Class>:) ofCommonAncestor:<Class>.class];
 }

 In subsequent subclasses of the root class that extend equality test:

 - (BOOL)isEqualTo<Class>:(<Class> *)anObject
 {
     if (anObject == self)
         return YES;
     else if (![anObject isKindOfClass:self.class])
         return NO;
     else if (![super isEqualTo<Class>:anObject])
         return NO;
     else
         return <memberwise comparison>;
 }

 @note Identity and -isKindOfClass: checks are only necessary if -isEqualTo<Class>: can be called outside of -isEqual:
       and guard against misuse. You may drop them if you can guarantee that no code calls it.
 */
- (BOOL)SR_isEqual:(nullable NSObject *)anObject usingSelector:(SEL)aSelector ofCommonAncestor:(Class)anAncestor;

@end

NS_ASSUME_NONNULL_END
