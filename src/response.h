#ifndef _RESPONSE_H_
#define _RESPONSE_H_

typedef struct {
    char headers[1024]; // http headers
    char *content; // contents, e.g. level data, song data, etc
} Response;

typedef struct {
    char body[512]; // make this so its heap allocated later
    char *requestLine[3]; // 0: METHOD, 1: ROUTE, 2: HTTP version
} Request;

// fills the response structure with information
void getResponse(char *request, Response *response);

// parses request and puts it into a Request structure
void ParseRequest(char *request, Request *splittedReq);

#endif // _RESPONSE_H_