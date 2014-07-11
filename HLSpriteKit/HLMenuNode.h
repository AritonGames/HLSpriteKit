//
//  HLMenuNode.h
//  HLSpriteKit
//
//  Created by Karl Voskuil on 5/1/14.
//  Copyright (c) 2014 Hilo. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>

#import "HLGestureTarget.h"

/**
 * HLMenuNode has an HLMenu, and it creates and displays label buttons for
 * each item in the HLMenu, stacked vertically.  Menus are hierarchical in
 * nature, and the scene provides functionality for navigating between menus
 * and submenus.
 */

@class HLLabelButtonNode;
@class HLMenuItem;
@class HLMenu;
@protocol HLMenuNodeDelegate;

typedef enum HLMenuNodeAnimation {
  HLMenuNodeAnimationNone,
  HLMenuNodeAnimationSlideLeft,
  HLMenuNodeAnimationSlideRight
} HLMenuNodeAnimation;

@interface HLMenuNode : SKNode <NSCoding, HLGestureTarget>

@property (nonatomic, weak) id<HLMenuNodeDelegate> delegate;

/**
 * The hierarchical menu displayed by the menu node.
 *
 * note: For the sake of simplicity, menu node does not worry about updating its
 * display when the caller makes changes to the individual menu items.  Instead,
 * it will only refresh the display after a call to setMenu:animation:.  The readonly
 * attribute helps to suggest this pattern.  More stringent would be to copy the
 * menu into the menu node, but that is deemed unnecessary.
 *
 * note: It is considered convenient for the menu node to keep a strong reference
 * to its menu, assuming that the caller typically wants a single fairly-static
 * menu hierarchy.  An alternate design, perhaps where only "current" menu is tracked,
 * should be considered if useful.
 */
@property (nonatomic, readonly, strong) HLMenu *menu;

@property (nonatomic, assign) CGFloat itemSpacing;

@property (nonatomic, strong) HLLabelButtonNode *itemButtonPrototype;

@property (nonatomic, assign) HLMenuNodeAnimation itemAnimation;

@property (nonatomic, assign) NSTimeInterval itemAnimationDuration;

@property (nonatomic, copy) NSString *itemSoundFile;

- (void)setMenu:(HLMenu *)menu animation:(HLMenuNodeAnimation)animation;

- (void)navigateToTopMenuAnimation:(HLMenuNodeAnimation)animation;

- (void)navigateToSubmenuWithPathComponents:(NSArray *)pathComponents animation:(HLMenuNodeAnimation)animation;

@end

@protocol HLMenuNodeDelegate <NSObject>

@optional

- (BOOL)menuNode:(HLMenuNode *)menuNode shouldTapMenuItem:(HLMenuItem *)menuItem itemIndex:(NSUInteger)itemIndex;

@required

- (void)menuNode:(HLMenuNode *)menuNode didTapMenuItem:(HLMenuItem *)menuItem itemIndex:(NSUInteger)itemIndex;

@end

/**
 * An HLMenuItem is a single item in an HLMenu.
 */

@interface HLMenuItem : NSObject <NSCoding>

@property (nonatomic, weak) HLMenu *parent;

@property (nonatomic, copy) NSString *text;

@property (nonatomic, strong) HLLabelButtonNode *buttonPrototype;

@property (nonatomic, copy) NSString *soundFile;

+ (HLMenuItem *)menuItemWithText:(NSString *)text;

- (id)initWithText:(NSString *)text;

- (NSArray *)pathComponents;

@end

/**
 * An HLMenu is a kind of menu item which can itself contain menu items.
 */

@interface HLMenu : HLMenuItem <NSCoding>

+ (HLMenu *)menuWithText:(NSString *)text items:(NSArray *)items;

- (id)initWithText:(NSString *)text items:(NSArray *)items;

- (void)addItem:(HLMenuItem *)item;

- (NSUInteger)itemCount;

- (HLMenuItem *)itemAtIndex:(NSUInteger)index;

- (HLMenuItem *)itemForPathComponents:(NSArray *)pathComponents;

- (void)removeAllItems;

@end

/**
 * An HLMenuBackItem is a kind of menu item which, when tapped,
 * navigates the menu scene to the parent of its parent menu.
 */

@interface HLMenuBackItem : HLMenuItem <NSCoding>

@end
