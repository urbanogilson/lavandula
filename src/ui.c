#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ui.h"

Page page(char *title) {
    Page page;
    page.title = strdup(title);
    page.bodyCount = 0;
    page.bodyCapacity = 1;
    page.body = malloc(sizeof(UIElement));
    
    return page;
}

UIElement newElement(ElementType type, void *data, RenderFunction render) {
    return (UIElement){
        .data = data,
        .type = type,
        .render = render
    };
}

void addElement(Page *page, UIElement element) {
    if (page->bodyCount >= page->bodyCapacity) {
        page->bodyCapacity *= 2;
        page->body = realloc(page->body, page->bodyCapacity * sizeof(UIElement));
    }
    page->body[page->bodyCount++] = element;
}

char *htmlFormat(const char *format, ...) {
    va_list args;

    va_start(args, format);
    int len = vsnprintf(NULL, 0, format, args);
    va_end(args);

    char *result = malloc(len + 1);
    if (!result) return NULL;

    va_start(args, format);
    vsnprintf(result, len + 1, format, args);
    va_end(args);

    return result;
}

static char *colourToStr(Colour colour) {
    switch (colour) {
        case COLOUR_BLACK: {
            return "BLACK";
        }
        case COLOUR_WHITE: {
            return "WHITE";
        }
        case COLOUR_GREEN: {
            return "GREEN";
        }
        case COLOUR_RED: {
            return "RED";
        }
        case COLOUR_BLUE: {
            return "BLUE";
        }
        default: {
            return "NONE";
        }
    }
}

void textSize(Text *text, TextSize size) {
    switch (size) {
        case TEXT_XS: {
            text->size = 12;
            break;
        }
        case TEXT_S: {
            text->size = 16;
            break;
        }
        case TEXT_M: {
            text->size = 20;
            break;
        }
        case TEXT_L: {
            text->size = 24;
            break;
        }
        case TEXT_XL: {
            text->size = 28;
            break;
        }
        case TEXT_XXL: {
            text->size = 32;
            break;
        }
        default: {
            text->size = 12;
            break;
        }
    }
}

void textColour(Text *text, Colour colour) {
    text->colour = colour;
}

void textWeight(Text *text, FontWeight weight) {
    text->weight = weight;
}

void textItalic(Text *text) {
    text->weight = FONT_ITALIC;
}

void textUnderline(Text *text) {
    text->underline = true;
}

void textStrikethrough(Text *text) {
    text->strikethrough = true;
}

void textBold(Text *text) {
    text->weight = FONT_BOLD;
}

void boxBorder(Box *box, Colour colour, int width) {
    box->hasBorder = true;
    box->borderColour = colour;
    box->borderWidth = width;
}

void boxPadding(Box *box, Padding *padding) {
    box->padding = padding;
}

void boxMargin(Box *box, Margin *margin) {
    box->margin = margin;
}

void buttonColour(Button *button, Colour colour) {
    button->background = colour;
}

void buttonTextColour(Button *button, Colour colour) {
    button->textColour = colour;
}

void check(Checkbox *checkbox) {
    checkbox->checked = true;
}

void uncheck(Checkbox *checkbox) {
    checkbox->checked = false;
}

void imageSize(Image *image, int width, int height) {
    image->width = width;
    image->height = height;
}

char *renderPadding(struct UIElement *element) {
    if (!element) return strdup("");
    return strdup("");
}

char *renderMargin(struct UIElement *element) {
    if (!element) return strdup("");
    return strdup("");
}

char *renderText(struct UIElement *element) {
    Text *t = (Text *)element->data;

    char *colourStr = colourToStr(t->colour);

    char *weightStr = (t->weight == FONT_BOLD || t->weight == FONT_BOLD_ITALIC) 
        ? "bold" : "normal";

    char *styleStr = (t->weight == FONT_ITALIC || t->weight == FONT_BOLD_ITALIC) 
        ? "italic" : "normal";


    char *html = htmlFormat(
        "<p id=\"%p\" style=\"color: %s; font-size: %dpx; font-weight:%s; font-style:%s;\">%s</p>",
        t,
        colourStr,
        t->size,
        weightStr,
        styleStr,
        t->text
    );

    return html;
}

char *renderLink(struct UIElement *element) {
    Link *l = (Link *)element->data;

    char *html = htmlFormat(
        "<a href=\"%s\">%s</a>",
        l->href,
        l->text
    );

    return html;
}

char *renderImage(UIElement *element) {
    Image *img = (Image *)element->data;
    char *html = htmlFormat(
        "<img src=\"%s\" alt=\"%s\" %s %s>",
        img->src,
        img->alt,
        img->width > 0 ? htmlFormat("width=\"%d\"", img->width) : "",
        img->height > 0 ? htmlFormat("height=\"%d\"", img->height) : ""
    );
    return html;
}

char *renderBox(struct UIElement *element) {
    Box *b = (Box *)element->data;

    int topPadding = 0;
    int bottomPadding = 0;
    int leftPadding = 0;
    int rightPadding = 0;
    if (b->padding) {
        topPadding = b->padding->top;
        bottomPadding = b->padding->bottom;
        leftPadding = b->padding->left;
        rightPadding = b->padding->right;
    }

    int topMargin = 0;
    int bottomMargin = 0;
    int leftMargin = 0;
    int rightMargin = 0;
    if (b->padding) {
        topMargin = b->margin->top;
        bottomMargin = b->margin->bottom;
        leftMargin = b->margin->left;
        rightMargin = b->margin->right;
    }

    char *html = htmlFormat(
        "<div style=\""
        "height:%dpx; width:%dpx; border:%dpx solid %s; "
        "padding:%dpx %dpx %dpx %dpx; "
        "margin:%dpx %dpx %dpx %dpx; "
        "\">",
        b->height,
        b->width,
        b->hasBorder ? b->borderWidth : 0,
        colourToStr(b->borderColour),
        topPadding, rightPadding, bottomPadding, leftPadding,
        topMargin, rightMargin, bottomMargin, leftMargin
    );

    for (int i = 0; i < b->childCount; i++) {
        char *childHtml = b->children[i].render(&b->children[i]);
        char *newHtml = htmlFormat("%s%s", html, childHtml);
        free(html);
        free(childHtml);
        html = newHtml;
    }

    char *finalHtml = htmlFormat("%s</div>", html);
    free(html);

    return finalHtml;
}

char *renderRawHtml(UIElement *element) {
    RawHtml *html = (RawHtml *)element->data;
    return html->html;
}

char *renderButton(UIElement *element) {
    Button *button = (Button *)element->data;

    char *html = htmlFormat(
        "<button id=\"btn_%p\">%s</button>",
        button,
        button->label
    );
    return html;
}


char *renderCheckbox(UIElement *element) {
    Checkbox *c = (Checkbox *)element->data;
    char *html = htmlFormat(
        "<label><input type=\"checkbox\" %s> %s</label>",
        c->checked ? "checked" : "",
        c->label
    );
    return html;
}

char *renderTextInput(UIElement *element) {
    TextInput *t = (TextInput *)element->data;
    char *html = htmlFormat(
        "<input type=\"text\" placeholder=\"%s\" value=\"%s\">",
        t->placeholder,
        t->value
    );
    return html;
}

char *renderRow(UIElement *element) {
    Row *r = (Row *)element->data;

    char *html = strdup("<div style=\"display:flex; flex-direction:row; gap:4px;\">");

    for (int i = 0; i < r->childCount; i++) {
        char *childHtml = r->children[i].render(&r->children[i]);
        char *newHtml = malloc(strlen(html) + strlen(childHtml) + 1);
        strcpy(newHtml, html);
        strcat(newHtml, childHtml);
        free(html);
        free(childHtml);
        html = newHtml;
    }

    char *finalHtml = malloc(strlen(html) + strlen("</div>") + 1);
    strcpy(finalHtml, html);
    strcat(finalHtml, "</div>");
    free(html);

    return finalHtml;
}

char *renderColumn(struct UIElement *element) {
    Column *c = (Column *)element->data;

    char *html = strdup("<div style=\"display:flex; flex-direction:column; gap:4px;\">");

    for (int i = 0; i < c->childCount; i++) {
        char *childHtml = c->children[i].render(&c->children[i]);
        char *newHtml = malloc(strlen(html) + strlen(childHtml) + 1);
        strcpy(newHtml, html);
        strcat(newHtml, childHtml);
        free(html);
        free(childHtml);
        html = newHtml;
    }

    char *finalHtml = malloc(strlen(html) + strlen("</div>") + 1);
    strcpy(finalHtml, html);
    strcat(finalHtml, "</div>");
    free(html);

    return finalHtml;
}

void putInBox(Box *box, UIElement element)
{
    if (box->childCount >= box->childCapacity) {
        box->childCapacity *= 2;
        box->children = realloc(box->children, sizeof(UIElement) * box->childCapacity);
    }
    box->children[box->childCount++] = element;
}

void putInRow(Row *row, UIElement element) {
    if (row->childCount >= row->childCapacity) {
        row->childCapacity *= 2;
        row->children = realloc(row->children, sizeof(UIElement) * row->childCapacity);
    }
    row->children[row->childCount++] = element;
}

void putInColumn(Column *column, UIElement element) {
    if (column->childCount >= column->childCapacity) {
        column->childCapacity *= 2;
        column->children = realloc(column->children, sizeof(UIElement) * column->childCapacity);
    }
    column->children[column->childCount++] = element;
}

void putInPage(Page *page, UIElement element) {
    addElement(page, element);
}

Text *text(char *text) {
    Text *t = malloc(sizeof(Text));

    t->text = strdup(text);
    t->colour = COLOUR_BLACK;
    t->size = 12;

    UIElement element = newElement(ELEMENT_TEXT, t, renderText);
    t->element = element;
    
    return t;
}

Link *linkTo(char *href, char *text) {
    Link *l = malloc(sizeof(Link));

    l->href = href;
    l->text = text;

    UIElement element = newElement(ELEMENT_LINK_TO, l, renderLink);
    l->element = element;

    return l;
}

Box *box(int height, int width) {
    Box *b = malloc(sizeof(Box));

    b->height = height;
    b->width = width;
    b->borderColour = COLOUR_BLACK;
    b->hasBorder = false;
    b->borderWidth = 2;
    b->padding = NULL;

    b->childCount = 0;
    b->childCapacity = 1;
    b->children = malloc(sizeof(UIElement));

    UIElement element = newElement(ELEMENT_BOX, b, renderBox);
    b->element = element;

    return b;
}

RawHtml *html(char *html) {
    RawHtml *r = malloc(sizeof(RawHtml));

    r->html = strdup(html);

    UIElement element = newElement(ELEMENT_RAW_HTML, r, renderRawHtml);
    r->element = element;

    return r;
}

Button *button(char *label) {
    Button *b = malloc(sizeof(Button));

    b->background = COLOUR_WHITE;
    b->textColour = COLOUR_BLACK;
    b->enabled = true;
    b->label = strdup(label);

    b->element = newElement(ELEMENT_BUTTON, b, renderButton);

    return b;
}

TextInput *textInput(char *placeholder) {
    TextInput *t = malloc(sizeof(TextInput));
    t->placeholder = placeholder;
    t->value = "";

    t->element = newElement(ELEMENT_TEXT_INPUT, t, renderTextInput);

    return t;
}

Checkbox *checkbox(char *label) {
    Checkbox *c = malloc(sizeof(Checkbox));
    c->checked = false;
    c->label = strdup(label);

    c->element = newElement(ELEMENT_CHECKBOX, c, renderCheckbox);

    return c;
}

Image *image(char *src, char *alt) {
    Image *img = malloc(sizeof(Image));
    img->src = strdup(src);
    img->alt = alt ? strdup(alt) : strdup("");
    img->width = -1;
    img->height = -1;

    UIElement element = newElement(ELEMENT_IMAGE, img, renderImage);
    img->element = element;

    return img;
}

Padding *padding(int padding) {
    Padding *p = malloc(sizeof(Padding));

    p->top = padding;
    p->bottom = padding;
    p->left = padding;
    p->right = padding;    

    UIElement element = newElement(ELEMENT_PADDING, p, renderPadding);
    p->element = element;

    return p;
}

Margin *margin(int margin) {
    Margin *m = malloc(sizeof(Margin));

    m->top = margin;
    m->bottom = margin;
    m->left = margin;
    m->right = margin;    

    UIElement element = newElement(ELEMENT_MARGIN, m, renderMargin);
    m->element = element;

    return m;
}

Padding *paddingFrom(int top, int bottom, int left, int right) {
    Padding *p = malloc(sizeof(Padding));

    p->top = top;
    p->bottom = bottom;
    p->left = left;
    p->right = right;    

    UIElement element = newElement(ELEMENT_PADDING, p, renderPadding);
    p->element = element;

    return p;
}

Margin *marginFrom(int top, int bottom, int left, int right) {
    Margin *p = malloc(sizeof(Margin));

    p->top = top;
    p->bottom = bottom;
    p->left = left;
    p->right = right;    

    UIElement element = newElement(ELEMENT_MARGIN, p, renderMargin);
    p->element = element;

    return p;
}

Row *row() {
    Row *r = malloc(sizeof(Row));

    r->childCount = 0;
    r->childCapacity = 1;
    r->children = malloc(sizeof(UIElement));

    UIElement element = newElement(ELEMENT_ROW, r, renderRow);
    r->element = element;

    return r;
}

Column *column() {
    Column *c = malloc(sizeof(Column));

    c->childCount = 0;
    c->childCapacity = 1;
    c->children = malloc(sizeof(UIElement));

    UIElement element = newElement(ELEMENT_COLUMN, c, renderColumn);
    c->element = element;

    return c;
}

void buttonOnClick(Button *b, void (*callback)()) {
    b->onClick = callback;
}

State *newState(void *initialValue, void (*onChange)(struct State *state)) {
    State *s = malloc(sizeof(State));
    s->data = initialValue;
    s->onChange = onChange;
    return s;
}

void setState(State *s, void *newValue) {
    s->data = newValue;
    if (s->onChange) s->onChange(s);
}