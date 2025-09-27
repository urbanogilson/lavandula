#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "ui.h"

Page page(char *title) {
    Page page;
    page.title = title;
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

void setTextSize(Text *text, TextSize size) {
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

void setTextColour(Text *text, Colour colour) {
    text->colour = colour;
}

char *renderText(struct UIElement *element) {
    Text *t = (Text *)element->data;

    char *colourStr = colourToStr(t->colour);

    char *html = htmlFormat(
        "<p style=\"color: %s; font-size: %dpx\">%s</p>",
        colourStr,
        t->size,
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

char *renderBox(struct UIElement *element) {
    Box *b = (Box *)element->data;

    char *html = htmlFormat("<div style=\"height:%dpx; width:%dpx; border:1px solid black;\">", b->height, b->width);

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

void putInBox(Box *box, UIElement element) {
    if (box->childCount >= box->childCapacity) {
        box->childCapacity *= 2;
        box->children = realloc(box->children, sizeof(UIElement) * box->childCapacity);
    }
    box->children[box->childCount++] = element;
}

Text *text(Page *page, char *text) {
    Text *t = malloc(sizeof(Text));
    t->text = text;
    t->colour = COLOUR_BLACK;
    t->size = 12;

    UIElement element = newElement(ELEMENT_TEXT, t, renderText);
    addElement(page, element);

    return t;
}

UIElement textRaw(char *text) {
    Text *t = malloc(sizeof(Text));
    t->text = text;
    t->colour = COLOUR_BLACK;
    t->size = 12;

    UIElement element = newElement(ELEMENT_TEXT, t, renderText);
    return element;
}

Link *linkTo(Page *page, char *text, char *href) {
    Link *l = malloc(sizeof(Link));
    l->page = page;
    l->href = href;
    l->text = text;

    UIElement element = newElement(ELEMENT_LINK_TO, l, renderLink);
    addElement(page, element);

    return l;
}

Box *box(Page *page, int height, int width) {
    Box *b = malloc(sizeof(Box));
    b->height = height;
    b->width = width;

    b->childCount = 0;
    b->childCapacity = 1;
    b->children = malloc(sizeof(UIElement));

    UIElement element = newElement(ELEMENT_BOX, b, renderBox);
    addElement(page, element);

    return b;
}