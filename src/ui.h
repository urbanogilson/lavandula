#ifndef ui_h
#define ui_h

#include <stdbool.h>

typedef enum {
    ELEMENT_TEXT,
    ELEMENT_LINK_TO,
    ELEMENT_BOX,
    ELEMENT_ROW,
    ELEMENT_COLUMN,
    ELEMENT_RAW_HTML,
    ELEMENT_PADDING,
    ELEMENT_MARGIN
} ElementType;

typedef enum {
    COLOUR_RED,
    COLOUR_BLUE,
    COLOUR_GREEN,
    COLOUR_BLACK,
    COLOUR_WHITE,
} Colour;

typedef enum {
    TEXT_XS,
    TEXT_S,
    TEXT_M,
    TEXT_L,
    TEXT_XL,
    TEXT_XXL
} TextSize;

typedef enum {
    FONT_NORMAL,
    FONT_BOLD,
    FONT_ITALIC,
    FONT_BOLD_ITALIC
} FontWeight;

struct Page;
struct UIElement;

typedef char *(*RenderFunction)(struct UIElement *element);

typedef struct UIElement {
    ElementType type;
    void *data;
    RenderFunction render;
} UIElement;

typedef struct {
    UIElement *body;
    int   bodyCount;
    int   bodyCapacity;

    char *title;
} Page;

typedef struct {
    char  *text;
    Colour colour;
    int    size;
    FontWeight weight;
    bool underline;
    bool strikethrough;

    UIElement element;
} Text;

typedef struct {
    int top;
    int bottom;
    int left;
    int right;
    UIElement element;
} Padding;

typedef struct {
    int top;
    int bottom;
    int left;
    int right;
    UIElement element;
} Margin;

typedef struct {
    int height;
    int width;

    bool hasBorder;
    Colour borderColour;
    int borderWidth;
    Padding *padding;
    Margin *margin;

    UIElement *children;
    int childCount;
    int childCapacity;

    UIElement element;
} Box;

typedef struct {
    UIElement *children;
    int childCount;
    int childCapacity;

    UIElement element;
} Row;

typedef struct {
    UIElement *children;
    int childCount;
    int childCapacity;

    UIElement element;
} Column;

typedef struct {
    Page *page;
    char *text;
    char *href;

    UIElement element;
} Link;

typedef struct {
    char *html;
    UIElement element;
} RawHtml;


Page page(char *title);
Text *text(char *text);
Link *linkTo(char *href, char *text);
Row *row();
Column *column();
Box *box(int height, int width);
RawHtml *html(char *html);

Padding *paddingFrom(int top, int bottom, int left, int right);
Padding *padding(int padding);
Margin *marginFrom(int top, int bottom, int left, int right);
Margin *margin(int margin);

void putInBox(Box *box, UIElement element);
void putInRow(Row *row, UIElement element);
void putInColumn(Column *column, UIElement element);
void putInPage(Page *Page, UIElement element);

void textSize(Text *text, TextSize size);
void textColour(Text *text, Colour colour);

void textWeight(Text *text, FontWeight weight);
void textBold(Text *text);
void textItalic(Text *text);

void textUnderline(Text *text);
void textStrikethrough(Text *text);

void boxBorder(Box *box, Colour colour, int width);
void boxPadding(Box *box, Padding *padding);
void boxMargin(Box *box, Margin *margin);

#endif