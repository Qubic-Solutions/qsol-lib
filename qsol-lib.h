

/* Generated with cbindgen:0.26.0 */

/* DO NOT MODIFY THIS MANUALLY! This file was generated using cbindgen. See RunCbindgen.py */

#include <cstdarg>
#include <cstdint>
#include <cstdlib>
#include <ostream>
#include <new>

namespace qsol {
namespace lib {

/// the FfiConnectionReply contains everything for your miner to get started
/// the public_key field contains the public key that should be used for mining initially
///
/// solution_threshold and random_seed contain the epoch parameters required for mining
///
/// note that if the success field is false, all parameters will be zeroed
struct FfiConnectionReply {
    uint8_t public_key[32];
    uint32_t solution_threshold;
    uint8_t random_seed[32];
    bool success;
};

/// the FfiUpdateReply signals to the client if any parameters need to be updated
///
/// if the public key your client is using to mine is outdated, the update_public_key field
/// will be set to true, and the public_key field will contain the new public key that should be used for mining
/// there is no direct penalty for ignoring certain public keys and continuing to mine with an outdated one, however this creates
/// an unequal sol distribution and might lead to lower payouts if it has serious effects for the pool
///
/// if your epoch parameters are outdated (identified by 32 byte random seed) the update_epoch field will be true
/// updating epoch parameters is REQUIRED for sols to be recorded in the pool, as they will be marked invalid otherwise
/// other parameter changes (e.g. DATA_LENGTH, INFO_LENGTH etc) will require recoding/recompiling your miner and updating to the latest qsol-lib version
struct FfiUpdateReply {
    bool update_public_key;
    uint8_t public_key[32];
    bool update_epoch;
    uint8_t random_seed[32];
    uint32_t solution_threshold;
    bool success;
};

extern "C" {

/// call this function once when your miner starts
/// the pool will pick up the label (if provided)
///
/// miner_id is required to be a valid CStr as well as a 60 character upper case qubic ID
FfiConnectionReply qsol_connect(const int8_t *label, const int8_t *miner_id);

/// call this function every 10-20 seconds to keep the pool connection alive
///
/// miner_id is required to be a valid CStr as well as a 60 character upper case qubic ID
FfiUpdateReply update(float iterrate,
                      const uint8_t *public_key,
                      const uint8_t *random_seed,
                      int8_t *miner_id);

/// Submits valid nonce/public key combinations to the pool server for further processing
/// note that solutions are validated client sided to prevent spamming this function
/// Processing on an x86_64 CPU should take less than 1 second (using SSE registers for portability)
///
/// miner_id and dev_id are required to be valid CStr as well as 60 character upper case qubic IDs
///
/// returns: success state
bool submit_work(const uint8_t *public_key,
                 const uint8_t *nonce,
                 const int8_t *miner_id,
                 const int8_t *dev_id,
                 float dev_fee);

/// run this once to ensure that the FFI lib can log to stdout
/// if this function is not called, the error, warn and info functions won't work
/// additionally, the other functions won't display error messages
void init_logger();

/// runs error macro
/// example log:
/// [2024-02-07T18:44:39Z ERROR qsol_lib] test
void error(const int8_t *log);

/// runs warn macro
/// example log:
/// [2024-02-07T18:44:39Z WARN  qsol_lib] test
void warn(const int8_t *log);

/// runs info macro
/// example log:
/// [2024-02-07T18:44:39Z INFO  qsol_lib] test
void info(const int8_t *log);

} // extern "C"

} // namespace lib
} // namespace qsol
