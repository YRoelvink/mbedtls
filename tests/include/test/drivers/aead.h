/*
 * Test driver for AEAD driver entry points.
 */
/*  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef PSA_CRYPTO_TEST_DRIVERS_AEAD_H
#define PSA_CRYPTO_TEST_DRIVERS_AEAD_H

#include "mbedtls/build_info.h"

#if defined(PSA_CRYPTO_DRIVER_TEST)
#include <psa/crypto_driver_common.h>

typedef struct {
    /* If not PSA_SUCCESS, return this error code instead of processing the
     * function call. */
    psa_status_t forced_status;
    /* Count the amount of times AEAD driver functions are called. */
    unsigned long hits_encrypt;
    unsigned long hits_decrypt;
    unsigned long hits_encrypt_setup;
    unsigned long hits_decrypt_setup;
    unsigned long hits_set_nonce;
    unsigned long hits_set_lengths;
    unsigned long hits_update_ad;
    unsigned long hits_update;
    unsigned long hits_finish;
    unsigned long hits_verify;
    unsigned long hits_abort;

    /* Status returned by the last AEAD driver function call. */
    psa_status_t driver_status;
} mbedtls_test_driver_aead_hooks_t;

#define MBEDTLS_TEST_DRIVER_AEAD_INIT { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
static inline mbedtls_test_driver_aead_hooks_t
    mbedtls_test_driver_aead_hooks_init( void )
{
    const mbedtls_test_driver_aead_hooks_t v = MBEDTLS_TEST_DRIVER_AEAD_INIT;
    return( v );
}

extern mbedtls_test_driver_aead_hooks_t mbedtls_test_driver_aead_hooks;

psa_status_t mbedtls_test_transparent_aead_encrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, xalSize_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, xalSize_t nonce_length,
    const uint8_t *additional_data, xalSize_t additional_data_length,
    const uint8_t *plaintext, xalSize_t plaintext_length,
    uint8_t *ciphertext, xalSize_t ciphertext_size, xalSize_t *ciphertext_length );

psa_status_t mbedtls_test_transparent_aead_decrypt(
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, xalSize_t key_buffer_size,
    psa_algorithm_t alg,
    const uint8_t *nonce, xalSize_t nonce_length,
    const uint8_t *additional_data, xalSize_t additional_data_length,
    const uint8_t *ciphertext, xalSize_t ciphertext_length,
    uint8_t *plaintext, xalSize_t plaintext_size, xalSize_t *plaintext_length );

psa_status_t mbedtls_test_transparent_aead_encrypt_setup(
    mbedtls_transparent_test_driver_aead_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, xalSize_t key_buffer_size,
    psa_algorithm_t alg );

psa_status_t mbedtls_test_transparent_aead_decrypt_setup(
    mbedtls_transparent_test_driver_aead_operation_t *operation,
    const psa_key_attributes_t *attributes,
    const uint8_t *key_buffer, xalSize_t key_buffer_size,
    psa_algorithm_t alg );

psa_status_t mbedtls_test_transparent_aead_set_nonce(
    mbedtls_transparent_test_driver_aead_operation_t *operation,
    const uint8_t *nonce,
    xalSize_t nonce_length );

psa_status_t mbedtls_test_transparent_aead_set_lengths(
    mbedtls_transparent_test_driver_aead_operation_t *operation,
    xalSize_t ad_length,
    xalSize_t plaintext_length );

psa_status_t mbedtls_test_transparent_aead_update_ad(
    mbedtls_transparent_test_driver_aead_operation_t *operation,
    const uint8_t *input,
    xalSize_t input_length );

psa_status_t mbedtls_test_transparent_aead_update(
   mbedtls_transparent_test_driver_aead_operation_t *operation,
   const uint8_t *input,
   xalSize_t input_length,
   uint8_t *output,
   xalSize_t output_size,
   xalSize_t *output_length );

psa_status_t mbedtls_test_transparent_aead_finish(
   mbedtls_transparent_test_driver_aead_operation_t *operation,
   uint8_t *ciphertext,
   xalSize_t ciphertext_size,
   xalSize_t *ciphertext_length,
   uint8_t *tag,
   xalSize_t tag_size,
   xalSize_t *tag_length );

psa_status_t mbedtls_test_transparent_aead_verify(
   mbedtls_transparent_test_driver_aead_operation_t *operation,
   uint8_t *plaintext,
   xalSize_t plaintext_size,
   xalSize_t *plaintext_length,
   const uint8_t *tag,
   xalSize_t tag_length );

psa_status_t mbedtls_test_transparent_aead_abort(
   mbedtls_transparent_test_driver_aead_operation_t *operation );

#endif /* PSA_CRYPTO_DRIVER_TEST */
#endif /* PSA_CRYPTO_TEST_DRIVERS_AEAD_H */
