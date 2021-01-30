/**
 * \ingroup mdz_ansi library
 *
 * \author maxdz Software GmbH
 *
 * \par license
 * This file is subject to the terms and conditions defined in file 'LICENSE.txt', which is part of this source code package.
 *
 * \par description
 * mdz_ansi is dynamically-sized contiguous string, containing ASCII (0..127) and "ANSI" (128 - 255) characters. 
 *
 * Capacity - how many bytes of memory is reserved.
 * Size - how many characters are actually residing in a string, excluding terminating 0.
 *
 * "reserve" functions allocate/reallocate memory dynamically using malloc()/realloc().
 * "attach" functionality allows attaching contiguous block of memory to string, for using string functions on it.
 *
 */

#ifndef MDZ_ANSI_H
#define MDZ_ANSI_H

#include "mdz_types.h"

#ifdef __cplusplus
extern "C" 
{
#endif

/**
 * \defgroup Library init functions
 */

/**
 * Initializes ansi library. This function should be caled before any other function of the library.
 * \param pFirstNameHash - user first name hash code
 * \param pLastNameHash - user last name hash code
 * \param pEmailHash - user e-mail hash code
 * \param pLicenseHash - license hash code
 * \return:
 * mdz_true - if the initialization has succeed, otherwise false
 */
  mdz_bool mdz_ansi_init(const uint32_t* pFirstNameHash, const uint32_t* pLastNameHash, const uint32_t* pEmailHash, const uint32_t* pLicenseHash);

/**
 * Initializes ansi library. This function should be caled before any other function of the library.
 * Memory for license data starts at position pStart. Size of internal initialization structure is returned in pSize.
 * \param pFirstNameHash - user first name hash code
 * \param pLastNameHash - user last name hash code
 * \param pEmailHash - user e-mail hash code
 * \param pLicenseHash - license hash code
 * \param pStart - memory start position of license data
 * \param nAreaSize - size of available memory from pStart in bytes. Should be large enough for license data (> 500 bytes)
 * \param pOutSize - actual size of placed license data in bytes
 * \return:
 * mdz_true - if the initialization has succeed, otherwise false
 */
  mdz_bool mdz_ansi_init_attached(const uint32_t* pFirstNameHash, const uint32_t* pLastNameHash, const uint32_t* pEmailHash, const uint32_t* pLicenseHash, const char* pStart, size_t nAreaSize, size_t* pOutSize);

/**
 * Un-initializes ansi library and frees corresponding memory allocations.
 */
  void mdz_ansi_uninit(void);

/**
 * \defgroup Init and destroy functions
 */

/**
 * Create empty string with Capacity and Size 0.
 * \param nEmbedSize - size of "embedded part" of string. There is no "embedded part" if 0
 * \return:
 * NULL   - if library is not initialized with mdz_ansi_init() call
 * NULL   - if memory allocation failed
 * Result - pointer to string for use in other mdz_ansi functions
 */
struct mdz_Ansi* mdz_ansi_create(size_t nEmbedSize);

/**
 * Create empty string with Capacity and Size 0. Memory for mdz_Ansi structure starts at position pStart. Size of internal ansi structure (it is usually bigger than mdz_Ansi) is returned in pSize.
 * \param pStart - memory start position of mdz_Ansi structure
 * \param nAreaSizeBytes - size of available memory from pStart in bytes. Should be large enough for internal Ansi structure
 * \param pOutSize - returned actual size of placed internal ansi structure in bytes, may be NULL if not needed
 * \return:
 * NULL   - if library is not initialized with mdz_ansi_init() call
 * NULL   - if pStart == NULL or pSize == NULL
 * NULL   - if size in nSize is smaller than size of internal ansi structure
 * Result - pointer to string for use in other mdz_Ansi functions. Normally it equals to pStart
 */
struct mdz_Ansi* mdz_ansi_create_attached(const void* pStart, size_t nAreaSizeBytes, size_t* pOutSize);

/**
 * Destroy string including underlying data. After destroying, pointer to string is set to NULL.
 * If string is attached using mdz_ansi_createAttached(), free() will not be called.
 * If string data is attached using mdz_ansi_attachData(), m_pData will not be destroyed.
 * \param ppAnsi - pointer to pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 */
void mdz_ansi_destroy(struct mdz_Ansi** ppAnsi);

/**
 * Clear m_pData of string with setting Size in 0.
 * \param pAnsi - pointer to string returned by mdz_ansi_create()
 */
void mdz_ansi_clear(struct mdz_Ansi* pAnsi);

/**
 * Attach pre-allocated data to string, assigning pcData to m_pData. If attached, m_pData will not be destroyed in mdz_ansi_destroy()
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param pData - pointer to pre-allocated data to attach
 * \param nOffsetFromStart - position in pre-allocated data to attach from. Can be > 0
 * \param nCapacity - full capacity pre-allocated data in items
 * \param enAttachType - type of attachment. Only MDZ_ATTACH_ZEROSIZE and MDZ_ATTACH_SIZE_TERMINATOR are allowed
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_false - if pData == NULL (MDZ_ERROR_DATA), or nOffsetFromStart >= nCapacity (MDZ_ERROR_OFFSET), or invalid enAttachType (MDZ_ERROR_ATTACHTYPE)
 * mdz_true  - operation succeeded
 * \examples:
 * <text>You read some text data with BOM. BOM is 3 bytes, full read data size (including BOM) is 100 bytes. In that case nOffsetFromStart is 3 and nCapacity is 100 - to attach this data and process it.</text>
 */
mdz_bool mdz_ansi_attachData(struct mdz_Ansi* pAnsi, const char* pData, size_t nOffsetFromStart, size_t nCapacity, enum mdz_attach_type enAttachType);

/**
 * \defgroup Reserve capacity functions
 */

/**
 * Reserve nNewCapacity items for string. String Size does not change. Reservation is not made if m_pData is attached using mdz_ansi_attachData()
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nNewCapacity - new capacity in items to reserve
 * \return:
 * mdz_false - if pAnsi == NULL 
 * mdz_false - if memory allocation failed (MDZ_ERROR_ALLOCATION)
 * mdz_false - if nNewCapacity > Capacity and m_pData is attached using mdz_ansi_attachData() (MDZ_ERROR_ATTACHED)
 * mdz_true  - if nNewCapacity <= Capacity (MDZ_ERROR_CAPACITY)
 * mdz_true	 - reservation succeeded
 */
mdz_bool mdz_ansi_reserve(struct mdz_Ansi* pAnsi, size_t nNewCapacity);

/**
 * Reserve nNewCapacity items for string and initializes all items in cItem. May be called only on empty string (with Size == 0). After call, string Size equals to Capacity-1.
 * Reservation is not made if m_pData is attached using mdz_ansi_attachData() and nNewCapacity > Capacity
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nNewCapacity - capacity to reserve in items
 * \param cItem - item for string initialization
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_false - if memory allocation failed (MDZ_ERROR_ALLOCATION)
 * mdz_false - if Size > 0 (MDZ_ERROR_NONEMPTY)
 * mdz_false - if nNewCapacity > Capacity and m_pData is attached using mdz_ansi_attachData() (MDZ_ERROR_ATTACHED)
 * mdz_true  - if nNewCapacity <= Capacity (MDZ_ERROR_CAPACITY), initialization succeeded
 * mdz_true  - reservation and initialization succeeded
 */
mdz_bool mdz_ansi_reserveAndInit_async(struct mdz_Ansi* pAnsi, size_t nNewCapacity, char cItem, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_reserveAndInit(pAnsi, nNewCapacity, cItem) mdz_ansi_reserveAndInit_async(pAnsi, nNewCapacity, cItem, NULL)

/**
 * Return string Capacity in items.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Capacity - otherwise 
 */
size_t mdz_ansi_capacity(const struct mdz_Ansi* pAnsi);

/**
 * Return string Size in items.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Size     - otherwise
 */
size_t mdz_ansi_size(const struct mdz_Ansi* pAnsi);

/**
 * Set string Size. Size must be < Capacity (because of terminating 0)
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nNewSize - new Size to set string in
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_false  - if nNewSize >= Capacity (MDZ_ERROR_CAPACITY). String Size is not changed
 * mdz_true - if succeeded
 */
mdz_bool mdz_ansi_resize(struct mdz_Ansi* pAnsi, size_t nNewSize);

/**
 * Return string OffsetFromStart in items.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \return:
 * SIZE_MAX        - if pAnsi == NULL
 * OffsetFromStart - otherwise 
 */
size_t mdz_ansi_offsetFromStart(const struct mdz_Ansi* pAnsi);

/**
 * Return if string data is attached.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_false - if string data is not attached
 * mdz_true  - if string data is attached
*/
mdz_bool mdz_ansi_isAttachedData(const struct mdz_Ansi* pAnsi);

/**
 * Return string "embedded part" Size in items.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Result   - "embedded part" Size otherwise
 */
size_t mdz_ansi_embedSize(const struct mdz_Ansi* pAnsi);

/**
 * \defgroup Insert/remove functions
 */

/**
 * Insert nCount items in string. String m_pData and pItems cannot overlap, if reservation is allowed. Size grows on nCount.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based position to insert. If nLeftPos == Size or -1, items are appended. nLeftPos > Size is not allowed
 * \param pcItems - items to insert
 * \param nCount - number of items to insert or 0 if pcItems until 0-terminator should be used
 * \param bReserve - if mdz_true reserve capacity when there is not enough space for insertion, otherwise mdz_false
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_false - if bReserve == mdz_true and memory allocation failed (MDZ_ERROR_ALLOCATION)
 * mdz_false - if bReserve == mdz_true and there is not enough capacity for inserted data, but m_pData is attached using mdz_ansi_attachData() (MDZ_ERROR_ATTACHED)
 * mdz_false - if bReserve == mdz_false and there is not enough free Capacity in the string (MDZ_ERROR_CAPACITY)
 * mdz_true  - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > Size (MDZ_ERROR_BIGLEFT), or nCount is too big (MDZ_ERROR_BIGCOUNT). No insertion is made
 * mdz_true  - insertion succeeded
 */
mdz_bool mdz_ansi_insert_async(struct mdz_Ansi* pAnsi, size_t nLeftPos, const char* pcItems, size_t nCount, mdz_bool bReserve, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_insert(pAnsi, nLeftPos, pcItems, nCount, bReserve) mdz_ansi_insert_async(pAnsi, nLeftPos, pcItems, nCount, bReserve, NULL)

/**
 * \defgroup Find functions
 */

/**
 * Find first occurrence of cItem in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to search from left. Use 0 to search from the beginning of string
 * \param nRightPos - 0-based end position to search up to. Use Size-1 or -1 to search till the end of string
 * \param cItem - character to find
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Size     - if nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No search is made
 * Size     - if item(s) not found
 * Result   - 0-based position of first match
 * \examples:
 * "abcdefgh" : (pAnsi, 0, 7, 'd') => 3
 * "abcdefgh" : (pAnsi, 4, 7, 'd') => 8
 * "abcdefgh" : (pAnsi, 0, 2, 'd') => 8
 */
size_t mdz_ansi_findSingle_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, char cItem, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_findSingle(pAnsi, nLeftPos, nRightPos, cItem) mdz_ansi_findSingle_async(pAnsi, nLeftPos, nRightPos, cItem, NULL)

/**
  * Find first occurrence of pcItems in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
  * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
  * \param nLeftPos - 0-based start position to search from left. Use 0 to search from the beginning of string
  * \param nRightPos - 0-based end position to search up to. Use Size-1 or -1 to search till the end of string
  * \param pcItems - pointer to items to find
  * \param nCount - number of items to find or 0 if pcItems until 0-terminator should be used
  * \param enFindMethod - find method to use. See details in mdz_find_method description
  * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
  * \return:
  * SIZE_MAX - if pAnsi == NULL
  * Size     - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT), or nCount is too big (MDZ_ERROR_BIGCOUNT), or invalid enFindMethod (MDZ_ERROR_FINDMETHOD). No search is made
  * Size     - if item(s) not found
  * Result   - 0-based position of first match
  * \examples:
  * "abcdefgh" : (pAnsi, 0, 7, "abcd", 4, MDZ_FIND_AUTO) => 0
  * "abcdefgh" : (pAnsi, 1, 7, "abcd", 4, MDZ_FIND_AUTO) => 8
  * "abcdefgh" : (pAnsi, 0, 6, "efgh", 4, MDZ_FIND_AUTO) => 8
  * "abcdefgh" : (pAnsi, 0, 7, "bcd",  4, MDZ_FIND_AUTO) => 1
  * "aaaa"     : (pAnsi, 0, 3, "aa",   2, MDZ_FIND_AUTO) => 0
  * "aaaa"     : (pAnsi, 1, 3, "aa",   2, MDZ_FIND_AUTO) => 1
  */
size_t mdz_ansi_find_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_find_method enFindMethod, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_find(pAnsi, nLeftPos, nRightPos, pcItems, nCount, enFindMethod) mdz_ansi_find_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, enFindMethod, NULL)

/**
 * Find first occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to search from left. Use 0 to search from the beginning of string
 * \param nRightPos - 0-based end position to search up to. Use Size-1 or -1 to search till the end of string
 * \param pcItems - pointer to items to find
 * \param nCount - number of items to find or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Size     - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No search is made
 * Size     - if item(s) not found
 * Result   - 0-based position of first match
 * \examples:
 * "abcdefgh" : (pAnsi, 0, 7, "e@#", 3) => 4
 * "abcdefgh" : (pAnsi, 5, 7, "e@#", 3) => 8
 * "abcdefgh" : (pAnsi, 0, 3, "e@#", 3) => 8
 */
size_t mdz_ansi_firstOf_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_firstOf(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_firstOf_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * Find first non-occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to search from left. Use 0 to search from the beginning of string
 * \param nRightPos - 0-based end position to search up to. Use Size-1 or -1 to serch till the end of string
 * \param pcItems - pointer to items to find
 * \param nCount - number of items to find or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Size     - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No search is made
 * Size     - if non-occurence is not found
 * Result   - 0-based position of first match
 * \examples:
 * "abcdefgh" : (pAnsi, 0, 7, "cba#", 4) => 3
 * "abcdefgh" : (pAnsi, 0, 2, "cba#", 4) => 8
 */
size_t mdz_ansi_firstNotOf_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_firstNotOf(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_firstNotOf_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * Find last occurrence of cItem in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based end position to find up to. Use 0 to search till the beginning of string
 * \param nRightPos - 0-based start position to find from right. Use Size-1 or -1 to serch from the end of string
 * \param cItem - character to find
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Size     - if nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No search is made
 * Size     - if item(s) not found
 * Result   - 0-based position of first match
 * \examples:
 * "abcdefgh" : (pAnsi, 0, 7, 'd') => 3
 * "abcdefgh" : (pAnsi, 4, 7, 'd') => 8
 * "abcdefgh" : (pAnsi, 0, 2, 'd') => 8
 * "aaaa"     : (pAnsi, 0, 3, 'a') => 3
 */
size_t mdz_ansi_rfindSingle_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, char cItem, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_rfindSingle(pAnsi, nLeftPos, nRightPos, cItem) mdz_ansi_rfindSingle_async(pAnsi, nLeftPos, nRightPos, cItem, NULL)

/**
  * Find last occurrence of pcItems in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
  * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
  * \param nLeftPos - 0-based end position to find up to. Use 0 to search till the beginning of string
  * \param nRightPos - 0-based start position to find from right. Use Size-1 or -1 to serch from the end of string
  * \param pcItems - pointer to items to find
  * \param nCount - number of items to find or 0 if pcItems until 0-terminator should be used
  * \param enFindMethod - find method to use. See details in mdz_find_method description
  * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
  * \return:
  * SIZE_MAX - if pAnsi == NULL
  * Size     - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT), or nCount is too big (MDZ_ERROR_BIGCOUNT), or invalid enFindMethod (MDZ_ERROR_FINDMETHOD). No search is made
  * Size     - if item(s) not found
  * Result   - 0-based position of first match
  * \examples:
  * "abcdefgh" : (pAnsi, 0, 7, "abcd", 4) => 0
  * "abcdefgh" : (pAnsi, 1, 7, "abcd", 4) => 8
  * "abcdefgh" : (pAnsi, 0, 6, "efgh", 4) => 8
  * "abcdefgh" : (pAnsi, 0, 7, "bcd",  4) => 1
  * "aaaa"     : (pAnsi, 0, 3, "aa",   2) => 2
  * "aaaa"     : (pAnsi, 0, 2, "aa",   2) => 1
  */
size_t mdz_ansi_rfind_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_find_method enFindMethod, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_rfind(pAnsi, nLeftPos, nRightPos, pcItems, nCount, enFindMethod) mdz_ansi_rfind_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, enFindMethod, NULL)

/**
 * Find last occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based end position to search up to. Use 0 to search till the beginning of string
 * \param nRightPos - 0-based start position to search from right. Use Size-1 or -1 to serch from the end of string
 * \param pcItems - pointer to items to find
 * \param nCount - number of items to find or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Size     - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No search is made
 * Size     - if item(s) not found
 * Result   - 0-based position of first match
 * \examples:
 * "abcdefgh" : (pAnsi, 0, 7, "e@#", 3) => 4
 * "abcdefgh" : (pAnsi, 5, 7, "e@#", 3) => 8
 * "abcdefgh" : (pAnsi, 0, 3, "e@#", 3) => 8
 * "eeee"     : (pAnsi, 0, 3, "e@#", 3) => 3
 * "eeee"     : (pAnsi, 0, 2, "e@#", 3) => 2
 */
size_t mdz_ansi_lastOf_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_lastOf(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_lastOf_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * Find last non-occurrence of any item of pcItems in string. Returns 0-based position of match (if found), or string Size if not found, or SIZE_MAX if error.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based end position to search up to. Use 0 to search till the beginning of string
 * \param nRightPos - 0-based start position to search from right. Use Size-1 or -1 to serch from the end of string
 * \param pcItems - pointer to items to find
 * \param nCount - number of items to find or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * Size     - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No search is made
 * Size     - if non-occurence is not found
 * Result   - 0-based position of first match
 * \examples:
 * "abcdefgh" : (pAnsi, 0, 7, "cba#", 4) => 7
 * "abcdefgh" : (pAnsi, 0, 2, "hgf#", 4) => 4
 * "abcdefgh" : (pAnsi, 5, 7, "hgf#", 4) => 8
 */
size_t mdz_ansi_lastNotOf_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_lastNotOf(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_lastNotOf_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * \defgroup Insert/remove functions
 */

/**
 * Remove nCount item(s) starting from 0-based nLeftPos position. After the operation, Capacity doesn't change, Size decreases on nCount.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to remove item(s) from. Use 0 to remove from the beginning of string
 * \param nCount - number of item(s) to remove or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_true  - if nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nCount is too big (MDZ_ERROR_BIGCOUNT), or nLeftPos + nCount > Size (MDZ_ERROR_BIGLEFT). No removes are made
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_ansi_removeFrom_async(struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_removeFrom(pAnsi, nLeftPos, nCount) mdz_ansi_removeFrom_async(pAnsi, nLeftPos, nCount, NULL)

/**
 * Remove all ocurrences of nCount item(s) matching to pcItems, residing between nLeftPos and nRightPos. After remove(s) Capacity doesn't change, Size decreases on nCount of removed items.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to remove item(s) from. Use 0 to search from the beginning of string
 * \param nRightPos - 0-based end position to remove item(s) up to. Use Size-1 or -1 to serch till the end of string
 * \param pcItems - pointer to items to remove
 * \param nCount - number of item(s) to remove or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_true  - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT), or nCount is too big (MDZ_ERROR_BIGCOUNT). No removes are made
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_ansi_remove_async(struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_remove(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_remove_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * Remove items which are contained in pcItems from left, until first non-contained in pcItems item is reached.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to trim item(s) from left. Use 0 to trim from the beginning of string
 * \param nRightPos - 0-based end position to trim item(s) up to. Use Size-1 or -1 to trim till the end of string
 * \param pcItems - pointer to items to remove
 * \param nCount - number of items to remove or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_true  - if string is empty (MDZ_ERROR_EMPTY), or pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No trims are made
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_ansi_trimLeft_async(struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_trimLeft(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_trimLeft_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * Remove items which are contained in pcItems from right, until first non-contained in pcItems item is reached.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based end position to trim item(s) up to. Use 0 to trim till the beginning of string
 * \param nRightPos - 0-based start position to trim item(s) from right. Use Size-1 or -1 to trim from the end of string
 * \param pcItems - pointer to items to remove
 * \param nCount - number of items to remove or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_true  - if string is empty (MDZ_ERROR_EMPTY), or pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No removes are made
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_ansi_trimRight_async(struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_trimRight(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_trimRight_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * Remove items which are contained in pcItems from left and from right, until first non-contained in pcItems item is reached.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to trim item(s) from left. Use 0 to trim from the beginning of string
 * \param nRightPos - 0-based start position to trim item(s) from right. Use Size-1 or -1 to trim from the end of string
 * \param pcItems - pointer to items to remove
 * \param nCount - number of items to remove or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_true  - if string is empty (MDZ_ERROR_EMPTY), or pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No removes are made
 * mdz_true  - operation succeeded, otherwise mdz_false
 */
mdz_bool mdz_ansi_trim_async(struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_trim(pAnsi, nLeftPos, nRightPos, pcItems, nCount) mdz_ansi_trim_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, NULL)

/**
 * \defgroup Miscellaneous functions
 */

/**
 * Compare content of string with pcItems.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to compare from. Use 0 to compare from the beginning of string
 * \param pcItems - pointer to items to compare
 * \param nCount - number of items to compare or 0 if pcItems until 0-terminator should be used
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * MDZ_COMPARE_ERROR    - if pAnsi == NULL
 * MDZ_COMPARE_NONEQUAL - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos >= Size (MDZ_ERROR_BIGLEFT), or nCount is too big (MDZ_ERROR_BIGCOUNT). No comparison is made
 * MDZ_COMPARE_EQUAL or MDZ_COMPARE_NONEQUAL - Result of comparison
 */
enum mdz_compare_result mdz_ansi_compare_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, const char* pcItems, size_t nCount, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_compare(pAnsi, nLeftPos, pcItems, nCount) mdz_ansi_compare_async(pAnsi, nLeftPos, pcItems, nCount, NULL)

/**
 * Replace every occurence of pcItemsBefore with pcItemsAfter. There should be enough Capacity for replacing data.
 * \param pAnsi - pointer to astring returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to search for replace from. Use 0 to search from the beginning of string
 * \param nRightPos - 0-based end position to search for replace up to. Use Size-1 or -1 to seach till the end of string
 * \param pcItemsBefore - pointer to items to replace
 * \param nCountBefore - number of items to replace or 0 if pcItems until 0-terminator should be used
 * \param pcItemsAfter - pointer to items to replace with
 * \param nCountAfter - number of items to replace with or 0 if pcItems until 0-terminator should be used
 * \param bReserve - if mdz_true reserve capacity when there is not enough space for replacement, otherwise mdz_false
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * mdz_false - if pAnsi == NULL
 * mdz_false - if bReserve == mdz_true and there is not enough capacity for inserted data, but m_pData is attached using mdz_ansi_attachData() (MDZ_ERROR_ATTACHED)
 * mdz_false - if bReserve == mdz_false and there is not enough free Capacity in the string (MDZ_ERROR_CAPACITY)
 * mdz_true  - if pcItemsBefore == NULL (MDZ_ERROR_ITEMS), or nCountBefore == 0 and pcItemsBefore[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT), or nCountBefore is too big (MDZ_ERROR_BIGCOUNT). No replacements are made
 * mdz_true  - operation succeeded
 */
mdz_bool mdz_ansi_replace_async(struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItemsBefore, size_t nCountBefore, const char* pcItemsAfter, size_t nCountAfter, mdz_bool bReserve, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_replace(pAnsi, nLeftPos, nRightPos, pcItemsBefore, nCountBefore, pcItemsAfter, nCountAfter, bReserve) mdz_ansi_replace_async(pAnsi, nLeftPos, nRightPos, pcItemsBefore, nCountBefore, pcItemsAfter, nCountAfter, bReserve, NULL)

/**
 * Counts number of pcItems substring occurences in string.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to count from. Use 0 to count from the beginning of string
 * \param nRightPos - 0-based end position to count up to. Use Size-1 or -1 to count till the end of string
 * \param pcItems - items/substring to count
 * \param nCount - Size of substring to count or 0 if pcItems until 0-terminator should be used
 * \param enFindMethod - find method to use. See details in mdz_find_method description
 * \param bAllowOverlapped - mdz_true if overlapped substrings should be counted, otherwise mdz_false
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL
 * 0        - if pcItems == NULL (MDZ_ERROR_ITEMS), or nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT), or nCount is too big (MDZ_ERROR_BIGCOUNT), or invalid enFindMethod (MDZ_ERROR_FINDMETHOD). No counting is made
 * Result   - 0-based count of substring occurences. 0 if not found
 */
size_t mdz_ansi_count_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcItems, size_t nCount, enum mdz_find_method enFindMethod, mdz_bool bAllowOverlapped, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_count(pAnsi, nLeftPos, nRightPos, pcItems, nCount, enFindMethod, bAllowOverlapped) mdz_ansi_count_async(pAnsi, nLeftPos, nRightPos, pcItems, nCount, enFindMethod, bAllowOverlapped, NULL)

/**
 * Fills pSubAnsi with items from pAnsi, starting from nLeftPos and ending with one of pSeparators or nRightPos.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to get items from. Use 0 to start from the beginning of string
 * \param nRightPos - 0-based end position to get items up to. Use Size-1 or -1 to proceed till the end of string
 * \param pcSeparators - separators to get items up to
 * \param nSeparatorsCount - number of separators or 0 if pcSeparators until 0-terminator should be used
 * \param pSubAnsi - pointer to string where items should be copied. Data in pSubAnsi will be re-reserved to appropriate size if necessary
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL, or pSubAnsi == NULL (MDZ_ERROR_SUBCONTAINER), or reallocation of m_pData in pSubAnsi was necessary but failed (MDZ_ERROR_ALLOCATION)
 * Size     - if pcSeparators == NULL (MDZ_ERROR_ITEMS), or nSeparatorsCount == 0 (MDZ_ERROR_ZEROCOUNT), or nLeftPos > nRightPos (MDZ_ERROR_BIGLEFT), or nRightPos >= Size (MDZ_ERROR_BIGRIGHT). No copying is made
 * Result   - 0-based position after separator if found, or Size if not found
 */
size_t mdz_ansi_copySubAnsi_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nRightPos, const char* pcSeparators, size_t nSeparatorsCount, struct mdz_Ansi* pSubAnsi, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_copySubAnsi(pAnsi, nLeftPos, nRightPos, pcSeparators, nSeparatorsCount, pSubAnsi) mdz_ansi_copySubAnsi_async(pAnsi, nLeftPos, nRightPos, pcSeparators, nSeparatorsCount, pSubAnsi, NULL)

/**
 * Fills pSubAnsi with items from pAnsi, starting from nLeftPos and containing nCount items.
 * \param pAnsi - pointer to string returned by mdz_ansi_create() or mdz_ansi_create_attached()
 * \param nLeftPos - 0-based start position to get items from. Use 0 to start from the beginning of string
 * \param nCount - number of items to copy or 0 if pcItems until 0-terminator should be used
 * \param pSubAnsi - pointer to string where items should be copied. Data in pSubAnsi will be re-reserved to appropriate size if necessary
 * \param pAsyncData - pointer to shared async data for asynchronous call, or NULL if call should be synchronous
 * \return:
 * SIZE_MAX - if pAnsi == NULL, or pSubAnsi == NULL (MDZ_ERROR_SUBCONTAINER), or reallocation of m_pData in pSubAnsi was necessary but failed (MDZ_ERROR_ALLOCATION)
 * Size     - if nCount == 0 and pcItems[0] == 0 (MDZ_ERROR_ZEROCOUNT), or nCount is too big (MDZ_ERROR_BIGCOUNT), or nLeftPos + nCount > Size (MDZ_ERROR_BIGLEFT). No copying is made
 * Result   - 0-based position after copied data, or Size if copied until the end of pAnsi
 */
size_t mdz_ansi_copySubAnsiFrom_async(const struct mdz_Ansi* pAnsi, size_t nLeftPos, size_t nCount, struct mdz_Ansi* pSubAnsi, struct mdz_asyncData* pAsyncData);

#define mdz_ansi_copySubAnsiFrom(pAnsi, nLeftPos, nCount, pSubAnsi) mdz_ansi_copySubAnsiFrom_async(pAnsi, nLeftPos, nCount, pSubAnsi, NULL)

#ifdef __cplusplus
}
#endif

#endif
