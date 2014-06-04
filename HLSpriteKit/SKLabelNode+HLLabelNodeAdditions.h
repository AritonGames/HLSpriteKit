//
//  SKLabelNode+HLLabelNodeAdditions.h
//  HLSpriteKit
//
//  Created by Karl Voskuil on 6/3/14.
//  Copyright (c) 2014 Hilo. All rights reserved.
//

#import <SpriteKit/SpriteKit.h>

/**
 * A vertical alignment mode which can measure a label not only by its
 * current size (based on its current text) but alternately by its
 * inherent font metrics.
 *
 * In particular, these alignments are helpful when aligning a label
 * node to a background which must appear to frame the text in the
 * label; and even more particularly, when the text might change (or
 * be visually compared to other such labels-plus-background).  For
 * example, the caller might want to leave space in the background for
 * the font descender even if the current label contains no
 * descenders.
 *
 *   HLLabelNodeVerticalAlignText.  Measure the label using the exact
 *   height of the current text (for example, not including the font
 *   descender if the current text has no descending characters).
 *   Align the label by the center of that height.
 *
 *   HLLabelNodeVerticalAlignFont.  Measure the label using the full
 *   height of the font (regardless of the current text, and including
 *   both ascender and descender).  Align the label by the center of
 *   that height.  This means that the location of the baseline won't
 *   change depending on the current text; space will be reserved for
 *   ascenders and descenders.
 *
 *   HLLabelNodeVerticalAlignFontAscender.  Measure the label using
 *   the full ascender of the font, but excluding the descender
 *   (regardless of the current text).  Align the label by the center
 *   of that height.  This means that the location of the baseline
 *   won't change depending on the current text; space will be
 *   reserved for ascenders; any descenders in the current text will
 *   extend down below the space reserved for the label.  (This might
 *   be useful for all-caps text.)
 *
 *   HLLabelNodeVerticalAlignFontAscenderBias.  Partway between using
 *   the entire font height (including descender) and using only the
 *   ascender.  Can be useful where you want room for the descender,
 *   for instance for mixed-case text, and yet the full font height
 *   just seems to leave a little too much space below the baseline.
 */
typedef enum HLLabelNodeVerticalAlignmentMode {
  HLLabelNodeVerticalAlignText,
  HLLabelNodeVerticalAlignFont,
  HLLabelNodeVerticalAlignFontAscender,
  HLLabelNodeVerticalAlignFontAscenderBias
} HLLabelNodeVerticalAlignmentMode;

@interface SKLabelNode (HLLabelNodeAdditions)

- (void)getAlignmentInNode:(SKNode *)node
forHLVerticalAlignmentMode:(HLLabelNodeVerticalAlignmentMode)hlVerticalAlignmentMode
   skVerticalAlignmentMode:(SKLabelVerticalAlignmentMode *)skVerticalAlignmentMode
               labelHeight:(CGFloat *)labelHeight
                 yPosition:(CGFloat *)yPosition;

@end
