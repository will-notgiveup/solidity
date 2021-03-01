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
/**
 * Unit tests for the address checksum.
 */

#include <libsolidity/lsp/VFS.h>
#include <libsolidity/lsp/TextBuffer.h>
#include <libsolutil/Exceptions.h>

#include <test/Common.h>

#include <boost/test/unit_test.hpp>

using namespace std;

namespace solidity::lsp::test
{

BOOST_AUTO_TEST_SUITE(LSP)

BOOST_AUTO_TEST_CASE(VFS_create)
{
	vfs::VFS vfs;
	vfs.insert("file:///project/test.txt", "text", 1, "Hello, World\n");

	auto const file = vfs.find("file:///project/test.txt");
	BOOST_CHECK_NE(file, nullptr);

	BOOST_CHECK_EQUAL(file->path(), "file:///project/test.txt");
	BOOST_CHECK_EQUAL(file->languageId(), "text");
	BOOST_CHECK_EQUAL(file->version(), 1);

	BOOST_CHECK_EQUAL(file->contentString(), "Hello, World\n");
}

BOOST_AUTO_TEST_CASE(VFS_modify_erase)
{
	vfs::VFS vfs;
	vfs::File& file = vfs.insert("file:///project/test.txt", "text", 1, "Hello, World\n");
	file.modify(LineColumnRange{{0, 0}, {0, 1}}, "");

	BOOST_CHECK_EQUAL(file.contentString(), "ello, World\n");

	file.modify(LineColumnRange{{0, 4}, {0, 5}}, "");
	BOOST_CHECK_EQUAL(file.contentString(), "ello World\n");

	file.modify(LineColumnRange{{0, 4}, {0, 10}}, "");
	BOOST_CHECK_EQUAL(file.contentString(), "ello\n");
}

BOOST_AUTO_TEST_CASE(VFS_modify_erase_multiline)
{
	vfs::VFS vfs;
	vfs::File& file = vfs.insert("file:///project/test.txt", "text", 1, "Hello,\nWorld\nCrew\n");
	file.modify(LineColumnRange{{0, 1}, {2, 2}}, "");

	BOOST_CHECK_EQUAL(file.contentString(), "Hew\n");
}

BOOST_AUTO_TEST_CASE(VFS_modify_change)
{
	vfs::VFS vfs;
	vfs::File& file = vfs.insert("file:///project/test.txt", "text", 1, "Hello, World\n");
	file.modify(LineColumnRange{{0, 5}, {0, 6}}, ";");

	BOOST_CHECK_EQUAL(file.contentString(), "Hello; World\n");
}

BOOST_AUTO_TEST_CASE(VFS_modify_change_single_to_multi_line2)
{
	// replace fragment of a single line with 2 lines
	vfs::VFS vfs;
	vfs::File& file = vfs.insert("file:///project/test.txt", "text", 1, "Hello\nWorld\n");
	file.modify(LineColumnRange{{0, 1}, {0, 2}}, "{foo\nbar}");

	BOOST_CHECK_EQUAL(file.contentString(), "H{foo\nbar}llo\nWorld\n");
}

BOOST_AUTO_TEST_CASE(VFS_modify_change_single_to_multi_line3)
{
	// replace fragment of a single line with 3 lines
	vfs::VFS vfs;
	vfs::File& file = vfs.insert("file:///project/test.txt", "text", 1, "Hello\nWorld\n");
	file.modify(LineColumnRange{{0, 1}, {0, 2}}, "{foo\nbar\ncom}");

	BOOST_CHECK_EQUAL(file.contentString(), "H{foo\nbar\ncom}llo\nWorld\n");
}

BOOST_AUTO_TEST_CASE(VFS_modify_change_single_to_multi_line3_last_empty)
{
	// replace fragment of a single line with 3 lines
	vfs::VFS vfs;
	vfs::File& file = vfs.insert("file:///project/test.txt", "text", 1, "Hello\nWorld\n");
	file.modify(LineColumnRange{{0, 1}, {0, 2}}, "{foo\nbar}\n");

	BOOST_CHECK_EQUAL(file.contentString(), "H{foo\nbar}\nllo\nWorld\n");
}

BOOST_AUTO_TEST_CASE(VFS_modify_insert_at_the_beginning)
{
	TextBuffer text{"Hello, World\n"};

	text.replace(LineColumnRange{{0, 0}, {0, 0}}, "[");
	BOOST_CHECK_EQUAL(text.data(), "[Hello, World\n");

	TextBuffer text2{"Hello,\nWorld\n"};
	text2.replace(LineColumnRange{{1, 0}, {1, 0}}, "[");
	BOOST_CHECK_EQUAL(text2.data(), "Hello,\n[World\n");

	text2[LineColumnRange{{2, 0}, {2, 0}}] = "[";
	BOOST_CHECK_EQUAL(text2.data(), "Hello,\n[World\n[");
}

BOOST_AUTO_TEST_CASE(VFS_modify_insert)
{
	vfs::VFS vfs;
	vfs::File& file = vfs.insert("file:///project/test.txt", "text", 1, "Hello, World\n");
	file.modify(LineColumnRange{{0, 5}, {0, 5}}, ";");

	BOOST_CHECK_EQUAL(file.contentString(), "Hello;, World\n");
}

BOOST_AUTO_TEST_SUITE_END()

} // end namespace
