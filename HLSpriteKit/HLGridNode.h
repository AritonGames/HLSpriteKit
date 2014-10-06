//
//  HLGridNode.h
//  HLSpriteKit
//
//  Created by Karl Voskuil on 7/14/14.
//  Copyright (c) 2014 Hilo. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>

#import "HLComponentNode.h"
#import "HLGestureTarget.h"

@interface HLGridNode : HLComponentNode <HLGestureTarget>

/**
 * A callback invoked when a square in the grid is tapped.  The callback parameter is
 * passed as the index of the tapped square.  (Square indexes, here as elsewhere, start
 * at zero for the top-left square in the grid, and then increase to the right row by
 * row.)
 *
 * note: For now, use callbacks rather than delegation.
 */
@property (nonatomic, copy) void (^squareTappedBlock)(int squareIndex);

@property (nonatomic, strong) SKColor *backgroundColor;

@property (nonatomic, strong) SKColor *squareColor;

@property (nonatomic, strong) SKColor *highlightColor;

@property (nonatomic, assign) CGFloat enabledAlpha;
@property (nonatomic, assign) CGFloat disabledAlpha;

/**
 * The size of the overall grid node is derived from the layout-affecting parameters.
 * (Currently the layout-affecting parameters are all passed into the init method.)
 */
@property (nonatomic, readonly) CGSize size;

/**
 * The layout mode for the grid.  Primarily affects how squares are layed out when they
 * don't fit exactly into rows.
 *
 *   HLGridNodeLayoutModeFill: Squares in the last row of the grid are widened so that
 *                             the row space is divided evenly among them.
 *
 *   HLGridNodeLayoutModeAlignLeft: Squares in the last row of the grid align to the
 *                                  left, perhaps leaving extra space on the right.
 */
typedef enum HLGridNodeLayoutMode {
  HLGridNodeLayoutModeFill,
  HLGridNodeLayoutModeAlignLeft,
} HLGridNodeLayoutMode;

/**
 * Initialize with values for layout-affecting parameters.
 *
 * note: Currently the layout-affecting parameters are not properties, and so can't be set
 * individually, which helps avoid the problem where layout is redone multiple times as
 * each parameter is adjusted individually.
 *
 * @param The maximum number of squares to layout in a row.
 *
 * @param The total number of squares to create in the grid.
 *
 * @param The layout mode for the grid (pertaining chiefly to handling the layout of
 *        squares that don't fit exactly into rows); see HLGridNodeLayoutMode.
 *
 * @param The normal size of a square when it fits in a row; see HLGridNodeLayoutMode
 *        for exceptions.
 *
 * @param The distance, in pixels, between the edge of the background and the nearest
 *        squares.
 *
 * @param The distance, in pixels, between squares; the background color shows through in
 *        this area.
 */
- (instancetype)initWithGridWidth:(int)gridWidth
                      squareCount:(int)squareCount
                       layoutMode:(HLGridNodeLayoutMode)layoutMode
                       squareSize:(CGSize)squareSize
             backgroundBorderSize:(CGFloat)backgroundBorderSize
              squareSeparatorSize:(CGFloat)squareSeparatorSize NS_DESIGNATED_INITIALIZER;

/**
 * Set content nodes in the squares of the grid.  As many nodes as fit in the grid will be
 * shown, starting at the upper left of the grid and filling rows before columns; the rest
 * will be ignored.
 *
 * The square node that holds each content node has anchorPoint (0.5, 0.5).  Typically the
 * size of the square is squareSize; see HLGridNodeLayoutMode for exceptions.
 */
- (void)setContent:(NSArray *)contentNodes;

/**
 * Returns the index of the square at the passed location, or -1 for none.  The location
 * is expected to be in the coordinate system of this node.
 */
- (int)squareAtLocation:(CGPoint)location;

/**
 * Set enabled state of a square, setting its alpha either to enabledAlpha or
 * disabledAlpha.
 */
- (void)setEnabled:(BOOL)enabled forSquare:(int)squareIndex;

/**
 * Sets highlight state of a square, setting its color either to highlightColor or
 * squareColor.
 */
- (void)setHighlight:(BOOL)highlight forSquare:(int)squareIndex;

- (void)animateHighlight:(BOOL)finalHighlight
              blinkCount:(int)blinkCount
       halfCycleDuration:(NSTimeInterval)halfCycleDuration
               forSquare:(int)squareIndex
              completion:(void(^)(void))completion;

/**
 * Convenience method for managing highlight of a single square: Sets highlight YES for
 * the passed square, and sets highlight NO for the previously selected square (if any).
 */
- (void)setSelectionForSquare:(int)squareIndex;

/**
 * Convenience method for managing highlight of a single square: Animates highlight YES
 * for the passed square, and sets highlight NO for the previously selected square (if
 * any).
 */
- (void)animateSelectionBlinkCount:(int)blinkCount
                 halfCycleDuration:(NSTimeInterval)halfCycleDuration
                         forSquare:(int)squareIndex
                        completion:(void(^)(void))completion;

/**
 * Convenience method for managing highlight of a single square: Clears the highlight of
 * the last-selected square, if any.
 */
- (void)clearSelection;

@end
