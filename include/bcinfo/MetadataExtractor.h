/*
 * Copyright 2011, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ANDROID_BCINFO_METADATAEXTRACTOR_H__
#define __ANDROID_BCINFO_METADATAEXTRACTOR_H__

#include <cstddef>
#include <stdint.h>

namespace llvm {
  class NamedMDNode;
}

namespace bcinfo {

class MetadataExtractor {
 private:
  const char *mBitcode;
  size_t mBitcodeSize;

  size_t mExportVarCount;
  size_t mExportFuncCount;
  size_t mExportForEachSignatureCount;
  const uint32_t *mExportForEachSignatureList;

  size_t mPragmaCount;
  const char **mPragmaKeyList;
  const char **mPragmaValueList;

  size_t mObjectSlotCount;
  const uint32_t *mObjectSlotList;

  uint32_t mCompilerVersion;
  uint32_t mOptimizationLevel;

  // Helper functions for extraction
  bool populateForEachMetadata(const llvm::NamedMDNode *ExportForEachMetadata);
  bool populateObjectSlotMetadata(const llvm::NamedMDNode *ObjectSlotMetadata);
  void populatePragmaMetadata(const llvm::NamedMDNode *PragmaMetadata);

 public:
  /**
   * Reads metadata from \p bitcode.
   *
   * \param bitcode - input bitcode string.
   * \param bitcodeSize - length of \p bitcode string (in bytes).
   */
  MetadataExtractor(const char *bitcode, size_t bitcodeSize);

  ~MetadataExtractor();

  /**
   * Extract the actual metadata from the supplied bitcode.
   *
   * \return true on success and false if an error occurred.
   */
  bool extract();

  /**
   * \return number of exported global variables (slots) in this script/module.
   */
  size_t getExportVarCount() const {
    return mExportVarCount;
  }

  /**
   * \return number of exported global functions (slots) in this script/module.
   */
  size_t getExportFuncCount() const {
    return mExportFuncCount;
  }

  /**
   * \return number of exported ForEach functions in this script/module.
   */
  size_t getExportForEachSignatureCount() const {
    return mExportForEachSignatureCount;
  }

  /**
   * \return array of ForEach function signatures.
   */
  const uint32_t *getExportForEachSignatureList() const {
    return mExportForEachSignatureList;
  }

  /**
   * \return number of pragmas contained in pragmaKeyList and pragmaValueList.
   */
  size_t getPragmaCount() const {
    return mPragmaCount;
  }

  /**
   * \return pragma keys (the name for the pragma).
   */
  const char **getPragmaKeyList() const {
    return mPragmaKeyList;
  }

  /**
   * \return pragma values (contents corresponding to a particular pragma key).
   */
  const char **getPragmaValueList() const {
    return mPragmaValueList;
  }

  /**
   * \return number of object slots contained in objectSlotList.
   */
  size_t getObjectSlotCount() const {
    return mObjectSlotCount;
  }

  /**
   * \return array of object slot numbers that must be cleaned up by driver
   *         on script teardown.
   */
  const uint32_t *getObjectSlotList() const {
    return mObjectSlotList;
  }

  /**
   * \return compiler version that generated this bitcode.
   */
  uint32_t getCompilerVersion() const {
    return mCompilerVersion;
  }

  /**
   * \return compiler optimization level for this bitcode.
   */
  uint32_t getOptimizationLevel() const {
    return mOptimizationLevel;
  }
};

}  // namespace bcinfo

#endif  // __ANDROID_BCINFO_METADATAEXTRACTOR_H__
