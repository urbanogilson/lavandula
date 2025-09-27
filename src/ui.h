#ifndef ui_h
#define ui_h

typedef enum {
    ELEMENT_TEXT,
    ELEMENT_LINK_TO,
    ELEMENT_BOX,
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
} Text;

typedef struct {
    int height;
    int width;

    UIElement *children;
    int childCount;
    int childCapacity;
} Box;

typedef struct {
    Page *page;
    char *text;
    char *href;
} Link;

Page page(char *title);
Text *text(Page *page, char *text);
UIElement textRaw(char *text);

Link *linkTo(Page *page, char *text, char *href);

Box *box(Page *page, int height, int width);
void putInBox(Box *box, UIElement element);

void setTextSize(Text *text, TextSize size);
void setTextColour(Text *text, Colour colour);

char *renderText(struct UIElement *element);
UIElement newElement(ElementType type, void *data, RenderFunction render);

#endif