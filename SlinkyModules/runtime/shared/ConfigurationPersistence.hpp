#ifndef SLINKY_SHARE_908865236FB27A3DD4F0
#define SLINKY_SHARE_908865236FB27A3DD4F0
#include "WordInvoker.hpp"
#include "../native/verified/module_settings.hpp"
#include <cstdint>

namespace reconstruction::configuration {
using Word = std::uint64_t;
// Ordinary callees and module callbacks use the explicit native payload frame.
// Protected/platform providers retain distinct typed contracts: their saved
// register transports cannot be replaced by an ordinary return-value adapter.
struct Dependencies {
    void *context;
    std::uint8_t *image;
    RecoveredFrameInvoker calls;
    const std::uint16_t *(*environment)(void *, const std::uint16_t *name);
    std::uint64_t (*wideLength)(void *, const std::uint16_t *);
    void *(*allocateZeroed)(void *, std::uint64_t count, std::uint64_t size);
    void (*release)(void *, void *);
    void (*copyWide)(void *, std::uint16_t *destination, std::uint64_t capacity,
        const std::uint16_t *source, std::uint64_t sourceLength);
    std::uint64_t *(*formatOptions)(void *);
    std::uint32_t (*formatWide)(void *, std::uint64_t options,
        std::uint16_t *, std::uint64_t capacity, const std::uint16_t *format,
        Word locale, const Word *argumentWords);
    std::int32_t (*createDirectory)(void *, const std::uint16_t *, Word security);
    std::uint32_t (*lastError)(void *);
    Word (*openFile)(void *, const std::uint16_t *, std::uint32_t access,
        std::uint32_t sharing, Word security, std::uint32_t creation,
        std::uint32_t attributes, Word templateHandle);
    // Native4CCA2 transports the decoded writer in saved R12. The supplied
    // service must implement that provider; no RAX-return assumption is made.
    std::uint64_t (*writeService)(void *, std::uint32_t protectedEntryRva);
    std::int32_t (*write)(void *, std::uint64_t service, Word handle,
        const std::uint8_t *, std::uint32_t bytes, std::uint32_t *written,
        Word overlapped);
    void (*close)(void *, Word handle);
    // Incoming bits of the native stack DWORD at RBP+4. The slot persists
    // across retries and is read even when a writer reports failure.
    std::uint32_t incomingWriteCount;
    // The file-size and reader providers are independently decoded at the
    // recorded protected sites. The reader arrives in saved RDI, not RAX.
    std::uint32_t (*fileSize)(void *, Word handle, Word highSize);
    std::uint64_t (*readService)(void *,std::uint32_t protectedEntryRva);
    std::int32_t (*read)(void *,std::uint64_t service,Word handle,
        std::uint8_t *,std::uint32_t bytes,std::uint32_t *read,Word overlapped);
    std::int32_t (*deleteFile)(void *,const std::uint16_t *);
};

std::uint32_t initializePath_4c590(std::uint16_t **, const Dependencies &);
std::uint32_t appendPath_4c610(std::uint16_t **, const std::uint8_t *, const Dependencies &);
std::uint32_t formatPath_4c6a0(std::uint16_t *, std::uint64_t,
    const std::uint16_t *, const Word *, const Dependencies &);
void parentPath_4c700(std::uint16_t **, const Dependencies &);
std::uint32_t ensureDirectory_4c740(std::uint16_t **, const Dependencies &);
std::uint32_t deletePath_4c780(std::uint16_t **,const Dependencies &);
std::uint32_t readText_4ca30(std::uint16_t **,std::uint8_t **,const Dependencies &);
std::uint32_t writeText_4cc40(std::uint16_t **, const std::uint8_t *,
    std::uint8_t replace, const Dependencies &);
void releasePath_4cd20(std::uint16_t **, const Dependencies &);
std::uint8_t serializeModule_ce20(Word root, const std::uint8_t *descriptor,
    const Dependencies &);
Word profileRecords_eea0(const std::uint8_t *profiles, std::uint64_t *count);
Word serializeConfiguration_bc70(const std::uint8_t *registry,
    const std::uint8_t *profiles, const Dependencies &);
std::uint32_t saveConfiguration_bbd0(const std::uint8_t *registry,
    const std::uint8_t *profiles, const Dependencies &);
Word profileMetadata_ea90(const std::uint8_t *);
void setCurrentProfile_bfc0(const std::uint8_t *,const Dependencies &);
Word currentProfile_c1f0(const Dependencies &);
std::uint8_t pendingChanges_c200(const Dependencies &);
std::uint8_t applyModule_cd20(Word root,const std::uint8_t *registry,
    std::uint8_t *descriptor,const Dependencies &);
std::uint8_t applyProfile_c030(const std::uint8_t *text,
    const std::uint8_t *registry,const Dependencies &);
Word serializeProfile_c170(const std::uint8_t *registry,const Dependencies &);
std::uint32_t loadProfile_be40(const std::uint8_t *name,
    const std::uint8_t *registry,const Dependencies &);
std::uint32_t saveProfile_c0b0(const std::uint8_t *name,std::uint8_t replace,
    const std::uint8_t *registry,const Dependencies &);
Word forwardModuleBind_28a30(const std::uint8_t *registry,
    const std::uint8_t *descriptor,std::uint32_t bind,const Dependencies &);
}
#endif // SLINKY_SHARE_908865236FB27A3DD4F0
