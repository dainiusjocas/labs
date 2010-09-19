#ifndef __SPELLCAST_H__
#define __SPELLCAST_H__

#define BUFFLEN 1024
#define SOURCEBACKLOG = 1
#define CLIENTBACKLOG = 1

#define P_ERROR(str) fprintf(stderr, "Error occurred: %s\n", str)

typedef struct _stream_meta {
  char *name;
  char *genre;
  char *url;
  char *mime_type;
  unsigned int bitrate;
  unsigned short pub;
} stream_meta;

typedef struct _source_meta {
  stream_meta *stream_data;
  int sock_d;
} source_meta;

typedef struct _server_meta {
  stream_meta *server_data;
  char *notice;
  unsigned int metaint;
} server_meta;

typedef struct _client_meta {
  char *name;
  int sock_d;
} client_meta;

typedef struct _spellcast_server {
  server_meta *server_metadata;
  int source_port;
  int client_port;
} spellcast_server;


static spellcast_server* init_variables(int args, char *argv[]);
static void init_server(spellcast_server *srv);
static void dispose_server(spellcast_server *srv);

#endif