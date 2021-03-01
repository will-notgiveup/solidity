/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
// SPDX-License-Identifier: GPL-3.0
#pragma once

#include <libsolidity/lsp/LSPTypes.h>
#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>

namespace solidity::lsp
{

/// Manages a text buffer.
///
/// See https://en.wikipedia.org/wiki/Rope_(data_structure) for future improvements.
///
/// TODO: remove, use std::string bare with free functions for helpers
class TextBuffer
{
public:
	using value_type = std::string;
	using reference = value_type::reference;
	using const_reference = value_type::const_reference;

	explicit TextBuffer(std::string _contents = {}): m_buffer{std::move(_contents)} {}
	TextBuffer(TextBuffer&&) = default;
	TextBuffer(TextBuffer const&) = delete;
	TextBuffer& operator=(TextBuffer&&) = default;
	TextBuffer& operator=(TextBuffer const&) = delete;

	bool empty() const noexcept { return m_buffer.empty(); }
	size_t size() const noexcept { return m_buffer.size(); }
	std::string const& data() const noexcept { return m_buffer; }

	reference at(size_t i) { return m_buffer.at(i); }
	const_reference at(size_t i) const { return m_buffer.at(i); }

	std::string_view at(LineColumnRange _range) const
	{
		auto const [start, end] = offsetsOf(_range);
		return std::string_view(&*std::next(std::begin(m_buffer), static_cast<int>(start)), end - start);
	}

	langutil::LineColumn toPosition(size_t _offset) const noexcept;
	size_t toOffset(langutil::LineColumn _position) const noexcept;
	std::pair<size_t, size_t> offsetsOf(LineColumnRange _range) const noexcept;

	void replace(LineColumnRange _range, std::string const& _replacementText);
	void assign(std::string const& _text);

	struct IndexedAccess
	{
		TextBuffer& buf;
		LineColumnRange range;
		IndexedAccess(TextBuffer& _buf, LineColumnRange _range): buf{_buf}, range{_range} {}
		IndexedAccess& operator=(std::string const& _text) { buf.replace(range, _text); return *this; }
		bool operator==(std::string_view const& _rhs) const noexcept { return buf.at(range) == _rhs; }
		bool operator!=(std::string_view const& _rhs) const noexcept { return !(*this == _rhs); }
	};
	IndexedAccess operator[](LineColumnRange _range) { return IndexedAccess{*this, _range}; }

	struct ConstIndexedAccess
	{
		TextBuffer const& buf;
		LineColumnRange range;
		ConstIndexedAccess(TextBuffer const& _buf, LineColumnRange _range): buf{_buf}, range{_range} {}
		bool operator==(std::string_view const& _rhs) const noexcept { return buf.at(range) == _rhs; }
		bool operator!=(std::string_view const& _rhs) const noexcept { return !(*this == _rhs); }
	};
	ConstIndexedAccess operator[](LineColumnRange _range) const { return ConstIndexedAccess{*this, _range}; }

private:
	std::string m_buffer;
};

} // end namespace

namespace std
{
	inline ostream& operator<<(ostream& _os, solidity::lsp::TextBuffer const& _text)
	{
		_os << _text.data();
		return _os;
	}
}

namespace solidity::lsp
{
	inline size_t TextBuffer::toOffset(langutil::LineColumn _position) const noexcept
	{
		// TODO: take care of Unicode.
		size_t offset = 0;
		langutil::LineColumn current = {0, 0};
		while (current != _position && offset < m_buffer.size())
		{
			if (at(offset) != '\n')
			{
				current.column++;
			}
			else
			{
				current.line++;
				current.column = 0;
			}
			offset++;
		}
		return offset;
	}

	inline langutil::LineColumn TextBuffer::toPosition(size_t _offset) const noexcept
	{
		// TODO: take care of Unicode.
		langutil::LineColumn position{0, 0};
		for (size_t offset = 0; offset != _offset && offset < m_buffer.size(); ++offset)
		{
			if (at(offset) != '\n')
			{
				position.column++;
			}
			else
			{
				position.line++;
				position.column = 0;
			}
		}
		return position;
	}

	inline std::pair<size_t, size_t> TextBuffer::offsetsOf(LineColumnRange _range) const noexcept
	{
		return std::pair{
			toOffset(_range.start),
			toOffset(_range.end)
		};
	}

	inline void TextBuffer::replace(LineColumnRange _range, std::string const& _replacementText)
	{
		auto const [start, end] = offsetsOf(_range);
		m_buffer.replace(start, end - start, _replacementText);
	}

	inline void TextBuffer::assign(std::string const& _text)
	{
		m_buffer = _text;
	}
}
