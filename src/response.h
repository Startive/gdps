#ifndef _RESPONSE_H_
#define _RESPONSE_H

typedef struct {
    char headers[1024]; // http headers
    char *content; // contents, e.g. level data, song data, etc
    int contentLength; // length of contents
} Response;

// fills the response structure with information
void ResponseBuilder(char *request, Response *response);

#endif // _RESPONSE_H_