#ifndef __SPELLCAST_SERVER_H__
#define __SPELLCAST_SERVER_H__

#define BUFFLEN 1024
#define MAX_CLIENTS 10
#define MAX_SOURCES 5
#define SOURCEBACKLOG 5
#define CLIENTBACKLOG 5
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
  char *mountpoint;
} source_meta;

typedef struct _client_meta {
  char *name;
  int sock_d;
} client_meta;

typedef struct _server_meta {
  stream_meta *server_data;
  char *notice;
  unsigned int metaint;
} server_meta;

typedef struct _spellcast_server {
  server_meta *server_metadata;
  char *source_port;
  char *client_port;
  struct addrinfo hints;
  struct addrinfo *srv_src_addrinfo, *srv_cl_addrinfo;
  int src_sock;
  int cl_sock;
  fd_set read_socks;
  int latest_sock;
  client_meta* clients[MAX_CLIENTS];
  source_meta* sources[MAX_SOURCES];
  char buffer[BUFFLEN];
  int connected_sources;
  int connected_clients;
} spellcast_server;

static spellcast_server* init_variables(int , char *[]);
static int init_server(spellcast_server *);
static void dispose_server(spellcast_server *);
int create_access_point(struct addrinfo*, struct addrinfo**, char *);
static int run(spellcast_server *);
static int accept_source(spellcast_server *);
static int accept_client(spellcast_server *);

/* Protocol functions */
static void parse_source_details(char*, int, source_meta*);
#endif
