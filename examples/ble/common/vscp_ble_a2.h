#ifndef VSCP_BLE_A2_H
#define VSCP_BLE_A2_H
#include <stddef.h>
#include <stdint.h>
/* OpenSSL EVP reference backend. Production senders must persist epoch/sequence
 * before encryption. Key/prefix/permissions are provisioned externally. */
typedef struct {
    uint16_t company, key_id;
    uint32_t epoch, sequence;
    uint8_t guid[16], prefix[5], key[16];
} vscp_a2_sender;
typedef struct {
    uint16_t company, key_id;
    uint32_t highest_epoch, highest_sequence;
    int initialized;
    uint8_t guid[16], prefix[5], key[16];
} vscp_a2_receiver;
/* Encode one AD structure; returns byte count or 0 on error.
 * Caller MUST ensure nonce uniqueness; this function does not persist state. */
size_t vscp_a2_encode(uint8_t out[256], const vscp_a2_sender *s,
                      uint16_t head, uint16_t cls, uint16_t type,
                      const uint8_t *plaintext, size_t n);
/* Decrypt and verify; returns 1 on success, 0 on failure.
 * Caller MUST durably persist updated replay state before acting on event.
 * The function does not perform VSCP application authorization. */
int vscp_a2_decode(const uint8_t *frame, size_t len,
                   vscp_a2_receiver *r, uint8_t plaintext[200],
                   size_t *n, uint16_t *head, uint16_t *cls, uint16_t *type);
#endif
