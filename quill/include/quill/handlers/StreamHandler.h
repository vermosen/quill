/**
 * Copyright(c) 2020-present, Odysseas Georgoudis & quill contributors.
 * Distributed under the MIT License (http://opensource.org/licenses/MIT)
 */

#pragma once

#include "quill/detail/misc/Common.h"
#include "quill/handlers/Handler.h"
#include <cstdio>
#include <string>

namespace quill
{
class StreamHandler : public Handler
{
public:
  /**
   * Constructor
   * Uses the default pattern formatter
   * @param stream only stdout or stderr
   * @throws on invalid param
   */
  explicit StreamHandler(filename_t stream);

  ~StreamHandler() override = default;

  /**
   * Write a formatted log record to the stream
   * @param formatted_log_record input log record to write
   * @param log_record_timestamp log record timestamp
   */
  QUILL_ATTRIBUTE_HOT void write(fmt::memory_buffer const& formatted_log_record, std::chrono::nanoseconds log_record_timestamp) override;

  /**
   * Flushes the stream
   */
  void flush() noexcept override;

  QUILL_NODISCARD virtual filename_t const& filename() const noexcept;

protected:
  /**
   * Protected constructor used by the file handler
   * @param file_pointer a pointer to a FILE* used by the derived class
   * @param filename the name of the file
   */
  StreamHandler(FILE* file_pointer, filename_t filename);

protected:
  filename_t _filename;
  FILE* _file{nullptr};
};
} // namespace quill