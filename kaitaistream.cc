#include <kaitai/kaitaistream.h>

#include <endian.h>
#include <byteswap.h>

#include <iostream>
#include <vector>
#include <stdexcept>

kaitai::kstream::kstream(std::istream* io) {
    m_io = io;
    init();
}

kaitai::kstream::kstream(std::string& data): m_io_str(data) {
    m_io = &m_io_str;
    init();
}

void kaitai::kstream::init() {
    exceptions_enable();
    align_to_byte();
}

void kaitai::kstream::close() {
    //  m_io->close();
}

void kaitai::kstream::exceptions_enable() const {
    m_io->exceptions(
        std::istream::eofbit |
        std::istream::failbit |
        std::istream::badbit
    );
}

// ========================================================================
// Stream positioning
// ========================================================================

bool kaitai::kstream::is_eof() const {
    char t;
    m_io->exceptions(
        std::istream::badbit
    );
    m_io->get(t);
    if (m_io->eof()) {
        m_io->clear();
        exceptions_enable();
        return true;
    } else {
        m_io->unget();
        exceptions_enable();
        return false;
    }
}

void kaitai::kstream::seek(uint64_t pos) {
    m_io->seekg(pos);
}

uint64_t kaitai::kstream::pos() {
    return m_io->tellg();
}

uint64_t kaitai::kstream::size() {
    std::ifstream::pos_type cur_pos = m_io->tellg();
    m_io->seekg(0, std::ios::end);
    std::ifstream::pos_type len = m_io->tellg();
    m_io->seekg(cur_pos);
    return len;
}

// ========================================================================
// Integer numbers
// ========================================================================

// ------------------------------------------------------------------------
// Signed
// ------------------------------------------------------------------------

int8_t kaitai::kstream::read_s1() {
    char t;
    m_io->get(t);
    return t;
}

// ........................................................................
// Big-endian
// ........................................................................

int16_t kaitai::kstream::read_s2be() {
    int16_t t;
    m_io->read(reinterpret_cast<char *>(&t), 2);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_16(t);
#endif
    return t;
}

int32_t kaitai::kstream::read_s4be() {
    int32_t t;
    m_io->read(reinterpret_cast<char *>(&t), 4);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_32(t);
#endif
    return t;
}

int64_t kaitai::kstream::read_s8be() {
    int64_t t;
    m_io->read(reinterpret_cast<char *>(&t), 8);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_64(t);
#endif
    return t;
}

// ........................................................................
// Little-endian
// ........................................................................

int16_t kaitai::kstream::read_s2le() {
    int16_t t;
    m_io->read(reinterpret_cast<char *>(&t), 2);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_16(t);
#endif
    return t;
}

int32_t kaitai::kstream::read_s4le() {
    int32_t t;
    m_io->read(reinterpret_cast<char *>(&t), 4);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_32(t);
#endif
    return t;
}

int64_t kaitai::kstream::read_s8le() {
    int64_t t;
    m_io->read(reinterpret_cast<char *>(&t), 8);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_64(t);
#endif
    return t;
}

// ------------------------------------------------------------------------
// Unsigned
// ------------------------------------------------------------------------

uint8_t kaitai::kstream::read_u1() {
    char t;
    m_io->get(t);
    return t;
}

// ........................................................................
// Big-endian
// ........................................................................

uint16_t kaitai::kstream::read_u2be() {
    uint16_t t;
    m_io->read(reinterpret_cast<char *>(&t), 2);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_16(t);
#endif
    return t;
}

uint32_t kaitai::kstream::read_u4be() {
    uint32_t t;
    m_io->read(reinterpret_cast<char *>(&t), 4);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_32(t);
#endif
    return t;
}

uint64_t kaitai::kstream::read_u8be() {
    uint64_t t;
    m_io->read(reinterpret_cast<char *>(&t), 8);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_64(t);
#endif
    return t;
}

// ........................................................................
// Little-endian
// ........................................................................

uint16_t kaitai::kstream::read_u2le() {
    uint16_t t;
    m_io->read(reinterpret_cast<char *>(&t), 2);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_16(t);
#endif
    return t;
}

uint32_t kaitai::kstream::read_u4le() {
    uint32_t t;
    m_io->read(reinterpret_cast<char *>(&t), 4);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_32(t);
#endif
    return t;
}

uint64_t kaitai::kstream::read_u8le() {
    uint64_t t;
    m_io->read(reinterpret_cast<char *>(&t), 8);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_64(t);
#endif
    return t;
}

// ========================================================================
// Floating point numbers
// ========================================================================

// ........................................................................
// Big-endian
// ........................................................................

float kaitai::kstream::read_f4be() {
    uint32_t t;
    m_io->read(reinterpret_cast<char *>(&t), 4);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_32(t);
#endif
    return reinterpret_cast<float&>(t);
}

double kaitai::kstream::read_f8be() {
    uint64_t t;
    m_io->read(reinterpret_cast<char *>(&t), 8);
#if __BYTE_ORDER == __LITTLE_ENDIAN
    t = bswap_64(t);
#endif
    return reinterpret_cast<double&>(t);
}

// ........................................................................
// Little-endian
// ........................................................................

float kaitai::kstream::read_f4le() {
    uint32_t t;
    m_io->read(reinterpret_cast<char *>(&t), 4);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_32(t);
#endif
    return reinterpret_cast<float&>(t);
}

double kaitai::kstream::read_f8le() {
    uint64_t t;
    m_io->read(reinterpret_cast<char *>(&t), 8);
#if __BYTE_ORDER == __BIG_ENDIAN
    t = bswap_64(t);
#endif
    return reinterpret_cast<double&>(t);
}

// ========================================================================
// Unaligned bit values
// ========================================================================

void kaitai::kstream::align_to_byte() {
    m_bits_left = 0;
    m_bits = 0;
}

uint64_t kaitai::kstream::read_bits_int(int n) {
    int bits_needed = n - m_bits_left;
    if (bits_needed > 0) {
        // 1 bit  => 1 byte
        // 8 bits => 1 byte
        // 9 bits => 2 bytes
        int bytes_needed = ((bits_needed - 1) / 8) + 1;
        if (bytes_needed > 8)
            throw std::runtime_error("read_bits_int: more than 8 bytes requested");
        char buf[8];
        m_io->read(buf, bytes_needed);
        for (int i = 0; i < bytes_needed; i++) {
            uint8_t b = buf[i];
            m_bits <<= 8;
            m_bits |= b;
            m_bits_left += 8;
        }
    }

    // raw mask with required number of 1s, starting from lowest bit
    uint64_t mask = get_mask_ones(n);
    // shift mask to align with highest bits available in @bits
    int shift_bits = m_bits_left - n;
    mask <<= shift_bits;
    // derive reading result
    uint64_t res = (m_bits & mask) >> shift_bits;
    // clear top bits that we've just read => AND with 1s
    m_bits_left -= n;
    mask = get_mask_ones(m_bits_left);
    m_bits &= mask;

    return res;
}

uint64_t kaitai::kstream::get_mask_ones(int n) {
    if (n == 64) {
        return 0xFFFFFFFFFFFFFFFF;
    } else {
        return ((uint64_t) 1 << n) - 1;
    }
}

// ========================================================================
// Byte arrays
// ========================================================================

std::string kaitai::kstream::read_bytes(ssize_t len) {
    std::vector<char> result(len);
    m_io->read(&result[0], len);
    return std::string(result.begin(), result.end());
}

std::string kaitai::kstream::read_bytes_full() {
    std::ifstream::pos_type p1 = m_io->tellg();
    m_io->seekg(0, std::ios::end);
    std::ifstream::pos_type p2 = m_io->tellg();
    size_t len = p2 - p1;

    // Note: this requires a std::string to be backed with a
    // contiguous buffer. Officially, it's a only requirement since
    // C++11 (C++98 and C++03 didn't have this requirement), but all
    // major implementations had contiguous buffers anyway.
    std::string result(len, ' ');
    m_io->seekg(p1);
    m_io->read(&result[0], len);

    return result;
}

std::string kaitai::kstream::read_bytes_term(char term, bool include, bool consume, bool eos_error) {
    std::string result;
    std::getline(*m_io, result, term);
    if (m_io->eof()) {
        // encountered EOF
        if (eos_error) {
            // throw exception here
        }
    } else {
        // encountered terminator
        if (include)
            result.push_back(term);
        if (!consume)
            m_io->unget();
    }
    return result;
}

std::string kaitai::kstream::ensure_fixed_contents(std::string expected) {
    std::string actual = read_bytes(expected.length());

    if (actual != expected) {
        std::cout << "Fixed contents mismatch!\n";
        std::cout << actual << "\n";
        std::cout << expected << "\n";
    }

    return actual;
}

std::string kaitai::kstream::bytes_strip_right(std::string src, char pad_byte) {
    std::size_t new_len = src.length();

    while (src[new_len - 1] == pad_byte)
        new_len--;

    return src.substr(0, new_len);
}

std::string kaitai::kstream::bytes_terminate(std::string src, char term, bool include) {
    std::size_t new_len = 0;
    std::size_t max_len = src.length();

    while (new_len < max_len && src[new_len] != term)
        new_len++;

    if (include && new_len < max_len)
        new_len++;

    return src.substr(0, new_len);
}

// ========================================================================
// Byte array processing
// ========================================================================

std::string kaitai::kstream::process_xor_one(std::string data, uint8_t key) {
    int len = data.length();
    std::string result(len, ' ');

    for (int i = 0; i < len; i++)
        result[i] = data[i] ^ key;

    return result;
}

std::string kaitai::kstream::process_xor_many(std::string data, std::string key) {
    int len = data.length();
    int kl = key.length();
    std::string result(len, ' ');

    int ki = 0;
    for (int i = 0; i < len; i++) {
        result[i] = data[i] ^ key[ki];
        ki++;
        if (ki >= kl)
            ki = 0;
    }

    return result;
}

std::string kaitai::kstream::process_rotate_left(std::string data, int amount) {
    int len = data.length();
    std::string result(len, ' ');

    for (int i = 0; i < len; i++) {
        uint8_t bits = data[i];
        result[i] = (bits << amount) | (bits >> (8 - amount));
    }

    return result;
}

#define KS_ZLIB

#ifdef KS_ZLIB
#include <zlib.h>

std::string kaitai::kstream::process_zlib(std::string data) {
    int ret;

    unsigned char *src_ptr = reinterpret_cast<unsigned char*>(&data[0]);
    std::stringstream dst_strm;

    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;

    ret = inflateInit(&strm);
    if (ret != Z_OK)
        throw std::runtime_error("zlib: inflateInit error");

    strm.next_in = src_ptr;
    strm.avail_in = data.length();

    unsigned char outbuffer[ZLIB_BUF_SIZE];
    std::string outstring;

    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        strm.next_out = reinterpret_cast<Bytef*>(outbuffer);
        strm.avail_out = sizeof(outbuffer);

        ret = inflate(&strm, 0);

        if (outstring.size() < strm.total_out)
            outstring.append(reinterpret_cast<char*>(outbuffer), strm.total_out - outstring.size());
    } while (ret == Z_OK);

    if (ret != Z_STREAM_END) {          // an error occurred that was not EOF
        std::ostringstream exc_msg;
        exc_msg << "zlib: error #" << ret << "): " << strm.msg;
        throw std::runtime_error(exc_msg.str());
    }

    if (inflateEnd(&strm) != Z_OK)
        throw std::runtime_error("zlib: inflateEnd error");

    return outstring;
}
#endif

// ========================================================================
// Misc utility methods
// ========================================================================

int kaitai::kstream::mod(int a, int b) {
    if (b <= 0)
        throw std::invalid_argument("mod divisor <= 0");
    int r = a % b;
    if (r < 0)
        r += b;
    return r;
}

#include <stdio.h>
std::string kaitai::kstream::to_string(int val) {
    // if int is 32 bits, "-2147483648" is longest string representation
    //   => 11 chars + zero => 12 chars
    // if int is 64 bits, "-9223372036854775808" is longest
    //   => 20 chars + zero => 21 chars
    char buf[25];
    int got_len = snprintf(buf, sizeof(buf), "%d", val);

    // should never happen, but check nonetheless
    if (got_len > sizeof(buf))
        throw std::invalid_argument("integer is longer than string buffer");

    return std::string(buf);
}

#include <algorithm>
std::string kaitai::kstream::reverse(std::string val) {
    std::reverse(val.begin(), val.end());

    return val;
}

// ========================================================================
// Other internal methods
// ========================================================================

#undef KS_STR_ENCODING_ICONV

#ifndef KS_STR_DEFAULT_ENCODING
#define KS_STR_DEFAULT_ENCODING "UTF-8"
#endif

#ifdef KS_STR_ENCODING_ICONV

#include <iconv.h>
#include <cerrno>
#include <stdexcept>

std::string kaitai::kstream::bytes_to_str(std::string src, std::string src_enc) {
    iconv_t cd = iconv_open(KS_STR_DEFAULT_ENCODING, src_enc.c_str());

    if (cd == (iconv_t) -1) {
        if (errno == EINVAL) {
            throw std::runtime_error("invalid encoding pair conversion requested");
        } else {
            throw std::runtime_error("error opening iconv");
        }
    }

    size_t src_len = src.length();
    size_t src_left = src_len;

    // Start with a buffer length of double the source length.
    size_t dst_len = src_len * 2;
    std::string dst(dst_len, ' ');
    size_t dst_left = dst_len;

    char *src_ptr = &src[0];
    char *dst_ptr = &dst[0];

    while (true) {
        size_t res = iconv(cd, &src_ptr, &src_left, &dst_ptr, &dst_left);

        if (res == (size_t) -1) {
            if (errno == E2BIG) {
                // dst buffer is not enough to accomodate whole string
                // enlarge the buffer and try again
                size_t dst_used = dst_len - dst_left;
                dst_left += dst_len;
                dst_len += dst_len;
                dst.resize(dst_len);

                // dst.resize might have allocated destination buffer in another area
                // of memory, thus our previous pointer "dst" will be invalid; re-point
                // it using "dst_used".
                dst_ptr = &dst[dst_used];
            } else {
                throw std::runtime_error("iconv error");
            }
        } else {
            // conversion successful
            dst.resize(dst_len - dst_left);
            break;
        }
    }

    if (iconv_close(cd) != 0)
        throw std::runtime_error("iconv close error");

    return dst;
}
#else
std::string kaitai::kstream::bytes_to_str(std::string src, std::string src_enc) {
    return src;
}
#endif
