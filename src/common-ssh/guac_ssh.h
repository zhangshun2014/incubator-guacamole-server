/*
 * Copyright (C) 2015 Glyptodon LLC
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef GUAC_COMMON_SSH_H
#define GUAC_COMMON_SSH_H

#include <guacamole/client.h>
#include <guacamole/object.h>
#include <libssh2.h>

/**
 * Initializes the underlying SSH and encryption libraries used by Guacamole.
 * This function must be called before any other guac_common_ssh_*() functions
 * are called.
 *
 * @param client
 *     The Guacamole client that will be using SSH.
 *
 * @return
 *     Zero if initialization, or non-zero if an error occurs.
 */
int guac_common_ssh_init(guac_client* client);

/**
 * Cleans up the underlying SSH and encryption libraries used by Guacamole.
 * This function must be called once no other guac_common_ssh_*() functions
 * will be used.
 */
void guac_common_ssh_uninit();

/**
 * Connects to the SSH server running at the given hostname and port using the
 * given username and password for authentication.
 *
 * @param hostname
 *     The hostname of the SSH server to connect to.
 *
 * @param port
 *     The port to connect to on the given hostname.
 *
 * @param username
 *     The username to authenticate as.
 *
 * @param password
 *     The password to provide when authenticating as the given user.
 *
 * @return
 *     A new SSH session if the connection and authentication succeed, or
 *     NULL if the connection or authentication were not successful.
 */
LIBSSH2_SESSION* guac_common_ssh_connect_password(const char* hostname,
        int port, const char* username, const char* password);

/**
 * Connects to the SSH server running at the given hostname and port using the
 * given username and private key for authentication.
 *
 * @param hostname
 *     The hostname of the SSH server to connect to.
 *
 * @param port
 *     The port to connect to on the given hostname.
 *
 * @param username
 *     The username to authenticate as.
 *
 * @param private_key
 *     The base64-encoded private key to use when authenticating.
 *
 * @param passphrase
 *     The passphrase to use when importing the private key, if any, or NULL
 *     if no passphrase should be used.
 *
 * @return
 *     A new SSH session if the connection and authentication succeed, or
 *     NULL if the connection or authentication were not successful.
 */
LIBSSH2_SESSION* guac_common_ssh_connect_private_key(const char* hostname,
        int port, const char* username, const char* private_key,
        const char* passphrase);

/**
 * Creates a new Guacamole filesystem object which provides access to files
 * and directories via SFTP using the given SSH session. When the filesystem
 * will no longer be used, it must be explicitly destroyed with
 * guac_common_ssh_destroy_sftp_filesystem().
 *
 * @param client
 *     The Guacamole client which will be associated with the new filesystem
 *     object.
 *
 * @param name
 *     The name to send as the name of the filesystem.
 *
 * @param session
 *     The session to use to provide SFTP.
 *
 * @return
 *     A new Guacamole filesystem object, already configured to use SFTP for
 *     uploading and downloading files.
 */
guac_object* guac_common_ssh_create_sftp_filesystem(guac_client* client,
         const char* name, LIBSSH2_SESSION* session);

/**
 * Destroys the given filesystem object, disconnecting from SFTP and freeing
 * and associated resources.
 *
 * @param client
 *     The client associated with the filesystem object.
 *
 * @param object
 *     The filesystem object to destroy.
 */
void guac_common_ssh_destroy_sftp_filesystem(guac_client* client,
        guac_object* filesystem);

#endif

