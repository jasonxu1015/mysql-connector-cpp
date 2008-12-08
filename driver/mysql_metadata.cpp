/* Copyright (C) 2007 - 2008 MySQL AB, 2008 Sun Microsystems, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   There are special exceptions to the terms and conditions of the GPL
   as it is applied to this software. View the full text of the
   exception in file EXCEPTIONS-CONNECTOR-C++ in the directory of this
   software distribution.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdlib.h>
#include <memory>
#include "mysql_connection.h"
#include "mysql_metadata.h"
#include "mysql_constructed_resultset.h"
#include "mysql_statement.h"
#include "mysql_prepared_statement.h"

// For snprintf
#include <stdio.h>
#if defined(_WIN32) || defined(_WIN64)
#define snprintf _snprintf
#endif	//	_WIN32

#include "mysql_debug.h"
#include "mysql_util.h"

namespace sql
{
namespace mysql
{

#if 0
class DataType
{
	DataType();
public:
	enum {
		BIT = -7,
		TINYINT = -6,
		SMALLINT = 5,
		INTEGER = 4,
		BIGINT = -5,
		FLOAT = 6,
		REAL = 7,
		DOUBLE = 8,
		NUMERIC = 2,
		DECIMAL = 3,
		CHAR = 1,
		VARCHAR = 12,
		LONGVARCHAR = -1,
		DATE = 91,
		TIME = 92,
		TIMESTAMP = 93,
		BINARY = -2,
		VARBINARY = -3,
		LONGVARBINARY = -4,
		SQLNULL = 0,
		OTHER = 1111,
		OBJECT = 2000,
		DISTINCT = 2001,
		STRUCT = 2002,
		ARRAY = 2003,
		BLOB = 2004,
		CLOB = 2005,
		REF = 2006,
		BOOLEAN = 16
	};
};


struct TypeInfoDef
{
	const char *typeName;
	int dataType;
	unsigned int precision;
	const char *literalPrefix;
	const char *literalSuffix;
	const char *createParams;
	short nullable;
	bool caseSensitive;
	short searchable;
	bool isUnsigned;
	bool fixedPrecScale;
	bool autoIncrement;
	const char *localTypeName;
	unsigned int minScale;
	unsigned int maxScale;
	int sqlDataType;
	int sqlDateTimeSub;
	unsigned int numPrecRadix;
};

TypeInfoDef mysqlc_types[] = {

	// ------------- MySQL-Type: BIT. DBC-Type: Bit -------------
	{
		"BIT",								// Typename
		DataType::Bit,						// dbc-type
		DataType::BIT,						// dbc-type
		1,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"BIT",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ------------ MySQL-Type: BOOL. DBC-Type: Bit -------------
	{
		"BOOL",								// Typename
		DataType::BIT,						// dbc-type
		1,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"BOOL",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// --------- MySQL-Type: TINYINT DBC-Type: TINYINT ----------
	{
		"TINYINT",							// Typename
		DataType::TINYINT,					// dbc-type
		3,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M)] [UNSIGNED] [ZEROFILL]",		// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		true,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"TINYINT",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: BIGINT DBC-Type: BIGINT ----------
	{
		"BIGINT",							// Typename
		DataType::BIGINT,					// dbc-type
		19,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M)] [UNSIGNED] [ZEROFILL]",		// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		true,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"BIGINT",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: LONG VARBINARY DBC-Type: LONGVARBINARY ----------
	{
		"LONG VARBINARY",					// Typename
		DataType::LONGVARBINARY,			// dbc-type
		16777215,							// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		true,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"LONG VARBINARY",					// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: MEDIUMBLOB DBC-Type: LONGVARBINARY ----------
	{
		"MEDIUMBLOB",						// Typename
		DataType::LONGVARBINARY,			// dbc-type
		16777215,							// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		true,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"MEDIUMBLOB",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: LONGBLOB DBC-Type: LONGVARBINARY ----------
	{
		"LONGBLOB",							// Typename
		DataType::LONGVARBINARY,			// dbc-type
		0xFFFFFFFF,							// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		true,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"LONGBLOB",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: BLOB DBC-Type: LONGVARBINARY ----------
	{
		"BLOB",								// Typename
		DataType::LONGVARBINARY,			// dbc-type
		0xFFFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		true,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"BLOB",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: TINYBLOB DBC-Type: LONGVARBINARY ----------
	{
		"TINYBLOB",							// Typename
		DataType::LONGVARBINARY,			// dbc-type
		0xFFFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		true,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"TINYBLOB",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: VARBINARY DBC-Type: VARBINARY ----------
	{
		"VARBINARY",						// Typename
		DataType::VARBINARY,				// dbc-type
		0xFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"(M)",								// Create params
		DatabaseMetaData::typeNullable,		// nullable
		true,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"VARBINARY",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: BINARY DBC-Type: BINARY ----------
	{
		"BINARY",							// Typename
		DataType::BINARY,					// dbc-type
		0xFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"(M)",								// Create params
		DatabaseMetaData::typeNullable,		// nullable
		true,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"VARBINARY",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: LONG VARCHAR DBC-Type: LONG VARCHAR ----------
	{
		"LONG VARCHAR",						// Typename
		DataType::LONGVARCHAR,				// dbc-type
		0xFFFFFF,							// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"LONG VARCHAR",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: MEDIUMTEXT DBC-Type: LONG VARCHAR ----------
	{
		"MEDIUMTEXT",						// Typename
		DataType::LONGVARCHAR,				// dbc-type
		0xFFFFFF,							// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"MEDIUMTEXT",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: MEDIUMTEXT DBC-Type: LONG VARCHAR ----------
	{
		"MEDIUMTEXT",						// Typename
		DataType::LONGVARCHAR,				// dbc-type
		0xFFFFFF,							// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"MEDIUMTEXT",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: LONGTEXT DBC-Type: LONG VARCHAR ----------
	{
		"LONGTEXT",							// Typename
		DataType::LONGVARCHAR,				// dbc-type
		0xFFFFFF,							// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"LONGTEXT",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: TEXT DBC-Type: LONG VARCHAR ----------
	{
		"TEXT",								// Typename
		DataType::LONGVARCHAR,				// dbc-type
		0xFFFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"TEXT",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: TINYTEXT DBC-Type: LONG VARCHAR ----------
	{
		"TINYTEXT",							// Typename
		DataType::LONGVARCHAR,				// dbc-type
		0xFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"TINYTEXT",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: CHAR DBC-Type: CHAR ----------
	{
		"CHAR",								// Typename
		DataType::CHAR,						// dbc-type
		0xFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"(M)",								// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"NUMERIC",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: DECIMAL DBC-Type: DECIMAL ----------
	{
		"DECIMAL",							// Typename
		DataType::NUMERIC,					// dbc-type
		17,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M[,D])] [ZEROFILL]",				// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"DECIMAL",							// local type name
		-308,								// minimum scale
		308,								// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: NUMERIC DBC-Type: NUMERIC ----------
	{
		"NUMERIC",							// Typename
		DataType::NUMERIC,					// dbc-type
		17,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M[,D])] [ZEROFILL]",				// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"NUMERIC",							// local type name
		-308,								// minimum scale
		308,								// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: INTEGER DBC-Type: INTEGER ----------
	{
		"INTEGER",							// Typename
		DataType::NUMERIC,					// dbc-type
		10,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M)] [UNSIGNED] [ZEROFILL]",		// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		true,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"INTEGER",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: INT DBC-Type: INTEGER ----------
	{
		"INT",								// Typename
		DataType::INTEGER,					// dbc-type
		10,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M)] [UNSIGNED] [ZEROFILL]",		// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		true,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"INT",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: MEDIUMINT DBC-Type: INTEGER ----------
	{
		"MEDIUMINT",						// Typename
		DataType::INTEGER,					// dbc-type
		7,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M)] [UNSIGNED] [ZEROFILL]",		// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		true,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"MEDIUMINT",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: SMALLINT DBC-Type: INTEGER ----------
	{
		"SMALLINT",							// Typename
		DataType::INTEGER,					// dbc-type
		5,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M)] [UNSIGNED] [ZEROFILL]",		// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		true,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"SMALLINT",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: FLOAT DBC-Type: REAL ----------
	{
		"FLOAT",							// Typename
		DataType::REAL,						// dbc-type
		10,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M,D)] [ZEROFILL]",				// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"FLOAT",							// local type name
		-38,								// minimum scale
		38,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: DOUBLE DBC-Type: DOUBLE ----------
	{
		"DOUBLE",							// Typename
		DataType::DOUBLE,					// dbc-type
		17,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M,D)] [ZEROFILL]",				// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"DOUBLE",							// local type name
		-308,								// minimum scale
		308,								// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: DOUBLE PRECISION DBC-Type: DOUBLE ----------
	{
		"DOUBLE PRECISION",					// Typename
		DataType::DOUBLE,					// dbc-type
		17,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M,D)] [ZEROFILL]",				// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"DOUBLE PRECISION",					// local type name
		-308,								// minimum scale
		308,								// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: REAL DBC-Type: DOUBLE ----------
	{
		"REAL",								// Typename
		DataType::DOUBLE,					// dbc-type
		17,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"[(M,D)] [ZEROFILL]",				// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		true,								// auto_increment
		"REAL",								// local type name
		-308,								// minimum scale
		308,								// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: VARCHAR DBC-Type: VARCHAR ----------
	{
		"VARCHAR",							// Typename
		DataType::VARCHAR,					// dbc-type
		255,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"(M)",								// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"VARCHAR",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: ENUM DBC-Type: VARCHAR ----------
	{
		"ENUM",								// Typename
		DataType::VARCHAR,					// dbc-type
		0xFFFF,								// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"ENUM",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: SET DBC-Type: VARCHAR ----------
	{
		"SET",								// Typename
		DataType::VARCHAR,					// dbc-type
		64,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"SET",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: DATE DBC-Type: DATE ----------
	{
		"DATE",								// Typename
		DataType::DATE,						// dbc-type
		0,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"DATE",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: TIME DBC-Type: TIME ----------
	{
		"TIME",								// Typename
		DataType::TIME,						// dbc-type
		0,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"TIME",								// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: DATETIME DBC-Type: TIMESTAMP ----------
	{
		"DATETIME",							// Typename
		DataType::TIMESTAMP,				// dbc-type
		0,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"DATETIME",							// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: TIMESTAMP DBC-Type: TIMESTAMP ----------
	{
		"TIMESTAMP",						// Typename
		DataType::TIMESTAMP,				// dbc-type
		0,									// Precision
		"",									// Literal prefix
		"",									// Literal suffix
		"",									// Create params
		DatabaseMetaData::typeNullable,		// nullable
		false,								// case sensitive
		DatabaseMetaData::typeSearchable,	// searchable
		false,								// unsignable
		false,								// fixed_prec_scale
		false,								// auto_increment
		"TIMESTAMP",						// local type name
		0,									// minimum scale
		0,									// maximum scale
		0,									// sql data type (unsued)
		0,									// sql datetime sub (unsued)
		10									// num prec radix
	},

	// ----------- MySQL-Type: TIMESTAMP DBC-Type: TIMESTAMP ----------
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	}
};
#endif

/* {{{ my_i_to_a() -I- */
static inline char * my_i_to_a(char * buf, size_t buf_size, int a)
{
	snprintf(buf, buf_size, "%d", a);
	return buf;
}
/* }}} */



/* {{{ MySQL_ConnectionMetaData::MySQL_ConnectionMetaData() -I- */
MySQL_ConnectionMetaData::MySQL_ConnectionMetaData(MySQL_Connection * conn, sql::mysql::util::my_shared_ptr< MySQL_DebugLogger > * l)
  : connection(conn), logger(l? l->getReference():NULL)
{
	CPP_ENTER("MySQL_ConnectionMetaData::MySQL_ConnectionMetaData");
	server_version = mysql_get_server_version(connection->getMySQLHandle());
	lower_case_table_names = connection->getSessionVariable("lower_case_table_names");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::~MySQL_ConnectionMetaData() -I- */
MySQL_ConnectionMetaData::~MySQL_ConnectionMetaData()
{
	/* Don't remove the block or we can get into problems with logger */
	{
		CPP_ENTER("MySQL_ConnectionMetaData::~MySQL_ConnectionMetaData");
		CPP_INFO_FMT("this=%p", this);
	}
	logger->freeReference();
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSchemata() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getSchemata(const std::string& /*catalogName*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSchemata");
	std::auto_ptr<sql::Statement> stmt(connection->createStatement());
	return stmt->executeQuery("SHOW DATABASES");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSchemaObjects() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getSchemaObjects(const std::string& /* catalogName */, const std::string& schemaName, const std::string& objectType)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSchemaObjects");
	// for now catalog name is ignored
	std::string query;

	std::string schemata_where_clause;
	std::string tables_where_clause;
	std::string views_where_clause;
	std::string routines_where_clause;
	std::string triggers_where_clause;

	static std::string schemata_select_items("'schema' AS 'OBJECT_TYPE', CATALOG_NAME as 'CATALOG', SCHEMA_NAME as 'SCHEMA', SCHEMA_NAME as 'NAME'");
	static std::string tables_select_items("'table' AS 'OBJECT_TYPE', TABLE_CATALOG as 'CATALOG', TABLE_SCHEMA as 'SCHEMA', TABLE_NAME as 'NAME'");
	static std::string views_select_items("'view' AS 'OBJECT_TYPE', TABLE_CATALOG as 'CATALOG', TABLE_SCHEMA as 'SCHEMA', TABLE_NAME as 'NAME'");
	static std::string routines_select_items("ROUTINE_TYPE AS 'OBJECT_TYPE', ROUTINE_CATALOG as 'CATALOG', ROUTINE_SCHEMA as 'SCHEMA', ROUTINE_NAME as 'NAME'");
	static std::string triggers_select_items("'trigger' AS 'OBJECT_TYPE', TRIGGER_CATALOG as 'CATALOG', TRIGGER_SCHEMA as 'SCHEMA', TRIGGER_NAME as 'NAME'");

	static std::string schema_ddl_column("Create Database");
	static std::string table_ddl_column("Create Table");
	static std::string view_ddl_column("Create View");
	static std::string procedure_ddl_column("Create Procedure");
	static std::string function_ddl_column("Create Function");
	static std::string trigger_ddl_column("SQL Original Statement");

	if (schemaName.length() > 0) {
		tables_where_clause.append(" WHERE table_type<>'VIEW' AND table_schema = '").append(schemaName).append("' ");
		schemata_where_clause.append(" WHERE schema_name = '").append(schemaName).append("' ");
		views_where_clause.append(" WHERE table_schema = '").append(schemaName).append("' ");
		routines_where_clause.append(" WHERE routine_schema = '").append(schemaName).append("' ");
		triggers_where_clause.append(" WHERE trigger_schema = '").append(schemaName).append("' ");
	}

	if (objectType.length() == 0) { 
		query.append("SELECT ").append(tables_select_items)
			.append(" FROM information_schema.tables ").append(tables_where_clause)
			.append("UNION SELECT ").append(views_select_items)
			.append(" FROM information_schema.views ").append(views_where_clause)
			.append("UNION SELECT ").append(routines_select_items)
			.append(" FROM information_schema.routines ").append(routines_where_clause)
			.append("UNION SELECT ").append(triggers_select_items)
			.append(" FROM information_schema.triggers ").append(triggers_where_clause)
			;
	} else {
		if (objectType.compare("schema") == 0) {
			query.append("SELECT ")
				.append(schemata_select_items)
				.append(" FROM information_schema.schemata")
				.append(schemata_where_clause);
		} else if (objectType.compare("table") == 0) {
			query.append("SELECT ")
				.append(tables_select_items)
				.append(" FROM information_schema.tables")
				.append(tables_where_clause);
		} else if (objectType.compare("view") == 0) {
			query.append("SELECT ")
				.append(views_select_items)
				.append(" FROM information_schema.views")
				.append(views_where_clause);
		} else if (objectType.compare("routine") == 0) {
			query.append("SELECT ")
				.append(routines_select_items)
				.append(" FROM information_schema.routines")
				.append(routines_where_clause);
		} else if (objectType.compare("trigger") == 0) {
			query.append("SELECT ")
				.append(triggers_select_items)
				.append(" FROM information_schema.triggers")
				.append(triggers_where_clause);
		} else {
			throw sql::InvalidArgumentException("MySQLMetadata::getSchemaObjects: invalid 'objectType'");
		}
	}

	std::auto_ptr<sql::Statement> stmt1(connection->createStatement());
	std::auto_ptr<sql::ResultSet> native_rs(stmt1->executeQuery(query));
		
	int objtype_field_index = native_rs->findColumn("OBJECT_TYPE");
	int catalog_field_index = native_rs->findColumn("CATALOG");
	int schema_field_index = native_rs->findColumn("SCHEMA");
	int name_field_index = native_rs->findColumn("NAME");

	std::list<std::string> rs_data;

	std::map<std::string, std::string> trigger_name_map;
	std::map<std::string, std::string> trigger_ddl_map;

	// if we fetch triggers, then build DDL for them
	if ((objectType.compare("trigger") == 0) || objectType.empty()) {
		std::string trigger_ddl_query("SELECT ");
		trigger_ddl_query
			.append(triggers_select_items)
			.append(", EVENT_MANIPULATION, EVENT_OBJECT_SCHEMA, EVENT_OBJECT_TABLE, ACTION_ORDER, "
							"	ACTION_CONDITION, ACTION_STATEMENT, ACTION_ORIENTATION, ACTION_TIMING, DEFINER"
							"	FROM information_schema.triggers ")
			.append(triggers_where_clause);

		std::auto_ptr<sql::Statement> stmt2(connection->createStatement());
		std::auto_ptr<sql::ResultSet> trigger_ddl_rs(stmt2->executeQuery(trigger_ddl_query));

		// trigger specific fields: exclusion from the rule - 'show create trigger' is not supported by verions below 5.1.21
		// reproducing ddl based on metadata
		int event_manipulation_index = trigger_ddl_rs->findColumn("EVENT_MANIPULATION");
		int event_object_schema_index = trigger_ddl_rs->findColumn("EVENT_OBJECT_SCHEMA");
		int event_object_table_index = trigger_ddl_rs->findColumn("EVENT_OBJECT_TABLE");
		int action_statement_index = trigger_ddl_rs->findColumn("ACTION_STATEMENT");
		int action_timing_index = trigger_ddl_rs->findColumn("ACTION_TIMING");
		int definer_index = trigger_ddl_rs->findColumn("DEFINER");

		while (trigger_ddl_rs->next()) {
			std::string trigger_ddl;

			// quote definer, which is stored as unquoted string
			std::string quoted_definer;
			{
				quoted_definer = trigger_ddl_rs->getString(definer_index);
				const char *quot_sym = "`\0";
				size_t i = quoted_definer.find('@');
				if (std::string::npos != i)
				{
					quoted_definer.reserve(quoted_definer.size()+4);
					quoted_definer.insert(i+1, quot_sym);
					quoted_definer.insert(i, quot_sym);
				}
				quoted_definer.insert(0, quot_sym);
				quoted_definer.push_back(quot_sym[0]);
			}

			std::string key;
			key.append("`").append(trigger_ddl_rs->getString("schema"))
				.append("`.`").append(trigger_ddl_rs->getString("name")).append("`");

			{
				trigger_ddl
					.append("CREATE\nDEFINER=").append(quoted_definer)
					.append("\nTRIGGER ").append("`")
					.append(trigger_ddl_rs->getString("schema")).append("`.`").append(trigger_ddl_rs->getString("name")).append("`")
					.append("\n").append(trigger_ddl_rs->getString(action_timing_index))
					.append(" ").append(trigger_ddl_rs->getString(event_manipulation_index))
					.append(" ON `").append(trigger_ddl_rs->getString(event_object_schema_index))
					.append("`.`").append(trigger_ddl_rs->getString(event_object_table_index)).append("`")
					.append("\nFOR EACH ROW\n")
					.append(trigger_ddl_rs->getString(action_statement_index))
					.append("\n");
					trigger_ddl_map[key] = trigger_ddl;
			}

			{
				std::string trigger_name;
				trigger_name
					.append(trigger_ddl_rs->getString(event_object_table_index))
					.append(".")
					.append(trigger_ddl_rs->getString("name"));
					trigger_name_map[key] = trigger_name;
			}
		}
	}

	while(native_rs->next()) {
		std::string obj_type(native_rs->getString(objtype_field_index));
		std::string schema(native_rs->getString(schema_field_index));
		std::string name(native_rs->getString(name_field_index));

		if ((obj_type.compare("PROCEDURE") == 0) || (obj_type.compare("FUNCTION") == 0)) {
			rs_data.push_back("routine");
		} else {
			rs_data.push_back(obj_type);
		}
		rs_data.push_back(native_rs->getString(catalog_field_index));
		rs_data.push_back(schema);


		if (obj_type.compare("trigger") == 0) {
			std::string key;
			key.append("`").append(schema).append("`.`").append(name).append("`");
			rs_data.push_back(trigger_name_map[key]);
		} else {
			rs_data.push_back(name);
		}

		std::string ddl_query;
		std::string ddl_column;

		if (obj_type.compare("schema") == 0) {
			ddl_column = schema_ddl_column;
			ddl_query.append("SHOW CREATE SCHEMA `").append(name).append("`");
		} else if (obj_type.compare("table") == 0) {
			ddl_column = table_ddl_column;
			ddl_query.append("SHOW CREATE TABLE `")
				.append(schema).append("`.`")
				.append(name).append("`");
		} else if (obj_type.compare("view") == 0) {
			ddl_column = view_ddl_column;
			ddl_query.append("SHOW CREATE VIEW `")
				.append(schema).append("`.`")
				.append(name).append("`");
		} else if (obj_type.compare("PROCEDURE") == 0) {
			ddl_column = procedure_ddl_column;
			ddl_query.append("SHOW CREATE PROCEDURE `")
				.append(schema).append("`.`")
				.append(name).append("`");
		} else if (obj_type.compare("FUNCTION") == 0) {
			ddl_column = function_ddl_column;
			ddl_query.append("SHOW CREATE FUNCTION `")
				.append(schema).append("`.`")
				.append(name).append("`");
		} else if (obj_type.compare("trigger") == 0) {
			/*
			ddl_column= trigger_ddl_column;
			ddl_query.append("SHOW CREATE TRIGGER `")
				.append(schema).append("`.`")
				.append(name).append("`");
			*/
		} else {
			throw sql::InvalidArgumentException("MySQL_DatabaseMetaData::getSchemaObjects: invalid OBJECT_TYPE returned from query");
		}

		// due to bugs in server code some queries can fail. 
		// here we want to gather as much info as possible
		try  {
			std::string ddl;

			if (obj_type.compare("trigger") == 0) {
				//ddl
				//	.append("CREATE\nDEFINER=").append(trigger_ddl_rs->getString(definer_index))
				//	.append("\nTRIGGER ").append("`")
				//	.append(schema).append("`.`").append(name).append("`")
				//	.append("\n").append(trigger_ddl_rs->getString(action_timing_index))
				//	.append(" ").append(trigger_ddl_rs->getString(event_manipulation_index))
				//	.append(" ON `").append(trigger_ddl_rs->getString(event_object_schema_index))
				//	.append("`.`").append(trigger_ddl_rs->getString(event_object_table_index)).append("`")
				//	.append("\nFOR EACH ROW\n")
				//	.append(trigger_ddl_rs->getString(action_statement_index))
				//	.append("\n");

				std::string key;
				key.append("`").append(schema).append("`.`").append(name).append("`");

				std::map<std::string, std::string>::const_iterator it = trigger_ddl_map.find(key);
				if (it != trigger_ddl_map.end())
					ddl.append(it->second);
			} else {
				std::auto_ptr<sql::Statement> stmt3(connection->createStatement());
				std::auto_ptr<sql::ResultSet> sql_rs(stmt3->executeQuery(ddl_query));

				sql_rs->next();

				// this is a hack for views listed as tables
				int colIdx = sql_rs->findColumn(ddl_column);
				if ((colIdx == -1) && (obj_type.compare("table") == 0))
					colIdx = sql_rs->findColumn(view_ddl_column);

				ddl = sql_rs->getString(colIdx);
			}
			rs_data.push_back(ddl);
		} catch (sql::SQLException &) {
			rs_data.push_back("");
		}
	}

	std::list<std::string> rs_field_data;
	rs_field_data.push_back(std::string("OBJECT_TYPE"));
	rs_field_data.push_back(std::string("CATALOG"));
	rs_field_data.push_back(std::string("SCHEMA"));
	rs_field_data.push_back(std::string("NAME"));
	rs_field_data.push_back(std::string("DDL"));

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSchemaObjectTypes() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getSchemaObjectTypes()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSchemaObjectTypes");
	std::list<std::string> rs_data;
	rs_data.push_back("table");
	rs_data.push_back("view");
	rs_data.push_back("routine");
	rs_data.push_back("trigger");

	std::list<std::string> rs_field_data;
	rs_field_data.push_back("OBJECT_TYPE");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::allProceduresAreCallable() -I- */
bool
MySQL_ConnectionMetaData::allProceduresAreCallable()
{
	CPP_ENTER("MySQL_ConnectionMetaData::allProceduresAreCallable");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::allTablesAreSelectable() -I- */
bool
MySQL_ConnectionMetaData::allTablesAreSelectable()
{
	CPP_ENTER("MySQL_ConnectionMetaData::allTablesAreSelectable");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::dataDefinitionCausesTransactionCommit() -I- */
bool
MySQL_ConnectionMetaData::dataDefinitionCausesTransactionCommit()
{
	CPP_ENTER("MySQL_ConnectionMetaData::dataDefinitionCausesTransactionCommit");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::dataDefinitionIgnoredInTransactions() -I- */
bool
MySQL_ConnectionMetaData::dataDefinitionIgnoredInTransactions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::dataDefinitionIgnoredInTransactions");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::deletesAreDetected() -I- */
bool
MySQL_ConnectionMetaData::deletesAreDetected(int /*type*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::deletesAreDetected");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::doesMaxRowSizeIncludeBlobs() -I- */
bool
MySQL_ConnectionMetaData::doesMaxRowSizeIncludeBlobs()
{
	CPP_ENTER("MySQL_ConnectionMetaData::doesMaxRowSizeIncludeBlobs");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getAttributes() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getAttributes(const std::string& /*catalog*/, const std::string& /*schemaPattern*/,
										const std::string& /*typeNamePattern*/, const std::string& /*attributeNamePattern*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getAttributes");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("TABLE_CAT");
	rs_field_data.push_back("TYPE_SCHEMA");
	rs_field_data.push_back("TYPE_NAME");
	rs_field_data.push_back("ATTR_NAME");
	rs_field_data.push_back("ATTR_TYPE_NAME");
	rs_field_data.push_back("ATTR_SIZE");
	rs_field_data.push_back("DECIMAL_DIGITS");
	rs_field_data.push_back("NUM_PREC_RADIX");
	rs_field_data.push_back("NULLABLE");
	rs_field_data.push_back("REMARKS");
	rs_field_data.push_back("ATTR_DEF");
	rs_field_data.push_back("SQL_DATA_TYPE");
	rs_field_data.push_back("SQL_DATETIME_SUB");
	rs_field_data.push_back("CHAR_OCTET_LENGTH");
	rs_field_data.push_back("ORDINAL_POSITION");
	rs_field_data.push_back("IS_NULLABLE");
	rs_field_data.push_back("SCOPE_CATALOG");
	rs_field_data.push_back("SCOPE_SCHEMA");
	rs_field_data.push_back("SOURCE_DATA_TYPE");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getBestRowIdentifier() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getBestRowIdentifier(const std::string& catalog, const std::string& schema,
												const std::string& table, int /* scope */, bool /* nullable */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getBestRowIdentifier");
	char buf[12];
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;
	std::auto_ptr<sql::ResultSet> rs(getPrimaryKeys(catalog, schema, table));
	buf[sizeof(buf) - 1] = '\0';

	while (rs->next()) {
		std::string columnNamePattern(rs->getString(4));

		std::auto_ptr<sql::ResultSet> rsCols(getColumns(catalog, schema, table, columnNamePattern));
		if (rsCols->next()) {
			rs_data.push_back(my_i_to_a(buf, sizeof(buf) - 1, DatabaseMetaData::bestRowSession)); // scope
			rs_data.push_back(rs->getString(4));	// column_name
			rs_data.push_back(rsCols->getString(5)); // data type
			rs_data.push_back(rsCols->getString(6)); // type name
			rs_data.push_back(rsCols->getString(7)); // column size
			rs_data.push_back(rsCols->getString(8)); // buffer length
			rs_data.push_back(rsCols->getString(9)); // decimal digits
			rs_data.push_back(my_i_to_a(buf, sizeof(buf) - 1, DatabaseMetaData::bestRowNotPseudo));// pseudo column
		}
	}

	rs_field_data.push_back("SCOPE");
	rs_field_data.push_back("COLUMN_NAME");
	rs_field_data.push_back("DATA_TYPE");
	rs_field_data.push_back("TYPE_NAME");
	rs_field_data.push_back("COLUMN_SIZE");
	rs_field_data.push_back("BUFFER_LENGTH");
	rs_field_data.push_back("DECIMAL_DIGITS");
	rs_field_data.push_back("PSEUDO_COLUMN");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getCatalogs() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getCatalogs()
{
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("TABLE_CAT");
	rs_field_data.push_back("TABLE_SCHEM");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getCatalogSeparator() -I- */
const std::string&
MySQL_ConnectionMetaData::getCatalogSeparator()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getCatalogSeparator");
	static const std::string separator("");
	return separator;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getCatalogTerm() -I- */
const std::string&
MySQL_ConnectionMetaData::getCatalogTerm()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getCatalogTerm");
	static const std::string term("n/a");
	return term;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getColumnPrivileges() -U- */
sql::ResultSet *
MySQL_ConnectionMetaData::getColumnPrivileges(const std::string& /*catalog*/, const std::string& /*schema*/,
												const std::string& /*table*/, const std::string& /*columnNamePattern*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getColumnPrivileges");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::getColumnPrivileges");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getColumns() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getColumns(const std::string& /*catalog*/, const std::string& schemaPattern,
										const std::string& tableNamePattern, const std::string& columnNamePattern)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getColumns");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;


	rs_field_data.push_back("TABLE_CAT");
	rs_field_data.push_back("TABLE_SCHEM");
	rs_field_data.push_back("TABLE_NAME");
	rs_field_data.push_back("COLUMN_NAME");
	rs_field_data.push_back("DATA_TYPE");
	rs_field_data.push_back("TYPE_NAME");
	rs_field_data.push_back("COLUMN_SIZE");
	rs_field_data.push_back("TABLE_COMMENT");
	rs_field_data.push_back("BUFFER_LENGTH");
	rs_field_data.push_back("DECIMAL_DIGITS");
	rs_field_data.push_back("NUM_PREC_RADIX");
	rs_field_data.push_back("NULLABLE");
	rs_field_data.push_back("REMARKS");
	rs_field_data.push_back("COLUMN_DEFAULT");
	rs_field_data.push_back("SQL_DATA_TYPE");
	rs_field_data.push_back("SQL_DATETIME_SUB");
	rs_field_data.push_back("CHAR_OCTET_LENGTH");
	rs_field_data.push_back("ORDINAL_POSITION");
	rs_field_data.push_back("IS_NULLABLE");
#if 0
	rs_field_data.push_back("SCOPE_CATALOG");
	rs_field_data.push_back("SCOPE_SCHEMA");
	rs_field_data.push_back("SCOPE_TABLE");
	rs_field_data.push_back("IS_AUTOINCREMENT");
#endif

	if (server_version > 79999) {
#if 0
		static const std::string query("SELECT TABLE_CATALOG, TABLE_SCHEMA, TABLE_NAME, " \
							"IF(STRCMP(TABLE_TYPE,'BASE TABLE'), TABLE_TYPE, 'TABLE'), " \
							"TABLE_COMMENT FROM INFORMATION_SCHEMA.TABLES WHERE " \
							"TABLE_SCHEMA  LIKE ? AND TABLE_NAME LIKE ? " \
							"ORDER BY TABLE_TYPE, TABLE_SCHEMA, TABLE_NAME");
		std::string pattern1, pattern2;

		std::auto_ptr<sql::PreparedStatement> stmt(connection->prepareStatement(query));
		pattern1.append(schemaPattern.c_str());

		pattern2.append(tableNamePattern.c_str());

		stmt->setString(1, pattern1);
		stmt->setString(2, pattern2);

		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery());

		while (rs->next()) {
			std::list<std::string>::iterator it;
			for (it = types.begin(); it != types.end(); ++it) {
				if (*it == rs->getString(4)) {
					rs_data.push_back(rs->getString(1));
					rs_data.push_back(rs->getString(2));
					rs_data.push_back(rs->getString(3));
					rs_data.push_back(rs->getString(4));
					rs_data.push_back(rs->getString(5));
					break;
				}
			}
		}
#endif
	} else {
		/* get schemata */
		std::string query1("SHOW DATABASES LIKE '");
		query1.append(schemaPattern).append("'");
		char buf[12];
		buf[sizeof(buf) - 1] = '\0';

		std::auto_ptr<sql::Statement> stmt1(connection->createStatement());
		std::auto_ptr<sql::ResultSet> rs1(stmt1->executeQuery(query1));

		while (rs1->next()) {
			std::string current_schema(rs1->getString(1));
			std::string query2("SHOW TABLES FROM `");
			query2.append(current_schema).append("` LIKE '").append(tableNamePattern).append("'");

			std::auto_ptr<sql::Statement> stmt2(connection->createStatement());
			std::auto_ptr<sql::ResultSet> rs2(stmt2->executeQuery(query2));

			while (rs2->next()) {
				std::string current_table(rs2->getString(1));
				std::string query3("SELECT * FROM `");
				query3.append(current_schema).append("`.`").append(current_table).append("` WHERE 0=1");

				std::auto_ptr<sql::Statement> stmt3(connection->createStatement());
				std::auto_ptr<sql::ResultSet> rs3(stmt1->executeQuery(query3));
				sql::ResultSetMetaData * rs3_meta = rs3->getMetaData();

				std::string query4("SHOW FULL COLUMNS FROM `");
				query4.append(current_schema).append("`.`").append(current_table).append("` LIKE '").append(columnNamePattern).append("'");
				std::auto_ptr<sql::Statement> stmt4(connection->createStatement());
				std::auto_ptr<sql::ResultSet> rs4(stmt1->executeQuery(query4));

				while (rs4->next()) {
					for (unsigned int i = 1; i <= rs3_meta->getColumnCount(); i++) {
						/*
						  `SELECT * FROM XYZ WHERE 0=1` will return metadata about all
						  columns but `columnNamePattern` could be set. So, we can have different
						  number of rows/columns in the result sets which doesn't correspond.
						*/
						if (rs3_meta->getColumnName(i) == rs4->getString(1)) {
							rs_data.push_back("");								// Catalog
							rs_data.push_back(current_schema);					// Schema
							rs_data.push_back(current_table);					// Table
							rs_data.push_back(rs4->getString(1));				// Column
							rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) rs3_meta->getColumnType(i))); // Type
							rs_data.push_back(rs3_meta->getColumnTypeName(i));	// Type name
							rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) rs3_meta->getColumnDisplaySize(i))); // Column size
							rs_data.push_back("");								// Table comment
							rs_data.push_back("");								// Buffer length
							rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) rs3_meta->getScale(i))); // Decimal digits
							rs_data.push_back("10");							// NUM_PREC_RADIX
							rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) rs3_meta->isNullable(i))); // Is_nullable
							rs_data.push_back(rs4->getString(9));				// remarks
							rs_data.push_back(rs4->getString(6));				// default
							rs_data.push_back("");								// SQL_DATA_TYPE - unused
							rs_data.push_back("");								// SQL_DATETIME_SUB - unused
							rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) rs3_meta->getColumnDisplaySize(i))); // CHAR_OCTET_LENGTH
							rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) i)); // CHAR_OCTET_LENGTH
							rs_data.push_back(rs3_meta->isNullable(i)? "YES":"NO");		// IS_NULLABLE
#if 0
							rs_data.push_back("");				// SCOPE_CATALOG - unused
							rs_data.push_back("");				// SCOPE_SCHEMA - unused
							rs_data.push_back("");				// SCOPE_TABLE - unused
							rs_data.push_back("");				// IS_AUTOINCREMENT - unused
#endif
							/* don't iterate any more, we have found our column */
							break;
						}
					}
				}
			}
		}

	}
	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getConnection() -I- */
Connection *
MySQL_ConnectionMetaData::getConnection()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getConnection");
	return this->connection;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getCrossReference() -U- */
sql::ResultSet *
MySQL_ConnectionMetaData::getCrossReference(const std::string& /*primaryCatalog*/, const std::string& /*primarySchema*/,
											const std::string& /*primaryTable*/, const std::string& /*foreignCatalog*/,
											const std::string& /*foreignSchema*/, const std::string& /*foreignTable*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getCrossReference");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::getCrossReference");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDatabaseMajorVersion() -I- */
int
MySQL_ConnectionMetaData::getDatabaseMajorVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDatabaseMajorVersion");
	return server_version / 10000;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDatabaseMinorVersion() -I- */
int
MySQL_ConnectionMetaData::getDatabaseMinorVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDatabaseMinorVersion");
	return (server_version % 10000) / 100;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDatabasePatchVersion() -I- */
int
MySQL_ConnectionMetaData::getDatabasePatchVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDatabasePatchVersion");
	return server_version % 100;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDatabaseProductName() -I- */
const std::string&
MySQL_ConnectionMetaData::getDatabaseProductName()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDatabaseProductName");
	static const std::string product_name("MySQL");
	return product_name;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDatabaseProductVersion() -I- */
const std::string&
MySQL_ConnectionMetaData::getDatabaseProductVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDatabaseProductVersion");
	static const std::string product_version("5.1");
	return product_version;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDefaultTransactionIsolation() -I- */
int
MySQL_ConnectionMetaData::getDefaultTransactionIsolation()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDefaultTransactionIsolation");
	if (server_version >= 32336) {
		return TRANSACTION_READ_COMMITTED;
	}
	return TRANSACTION_NONE;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDriverMajorVersion() -I- */
int
MySQL_ConnectionMetaData::getDriverMajorVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDriverMajorVersion");
	return 1;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDriverMinorVersion() -I- */
int
MySQL_ConnectionMetaData::getDriverMinorVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDriverMinorVersion");
	return 0;
}
/* }}} */

/* {{{ MySQL_ConnectionMetaData::getDriverPatchVersion() -I- */
int
MySQL_ConnectionMetaData::getDriverPatchVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDriverPatchVersion");
	return 0;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDriverName() -I- */
const std::string&
MySQL_ConnectionMetaData::getDriverName()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDriverName");
	static const std::string product_version("MySQL CPP Connector");
	return product_version;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getDriverVersion() -I- */
const std::string&
MySQL_ConnectionMetaData::getDriverVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getDriverVersion");
	static const std::string version("1.0.2-beta");
	return version;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getExportedKeys() -U- */
sql::ResultSet *
MySQL_ConnectionMetaData::getExportedKeys(const std::string& /*catalog*/, const std::string& /*schema*/, const std::string& /*table*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getExportedKeys");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::getExportedKeys");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getExtraNameCharacters() -I- */
const std::string&
MySQL_ConnectionMetaData::getExtraNameCharacters()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getExtraNameCharacters");
	static const std::string extra("#@");
	return extra;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getIdentifierQuoteString() -I- */
const std::string&
MySQL_ConnectionMetaData::getIdentifierQuoteString()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getIdentifierQuoteString");
	static const std::string empty(" "), tick("`"), quote("\"");

	if (server_version >= 32306) {
		/* Ask the server for sql_mode and decide for a tick or a quote */
		std::string sql_mode(connection->getSessionVariable("SQL_MODE"));

		if (sql_mode.find("ANSI_QUOTES") != std::string::npos) {
			return quote;
		} else {
			return tick;
		}
	}
	return empty;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::parseImportedKeys() -I- */
bool
MySQL_ConnectionMetaData::parseImportedKeys(std::string& token, std::string & /* quoteIdentifier */, std::list< std::string > & /* fields */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::parseImportedKeys");
//	TODO
//	token = token.trim();

	/* check if line contains 'CONSTRAINT' */
	if (token.find("CONSTRAINT") != std::string::npos) {
		return false;
	}
#if 0
	int nIndex = 0, nextField = -1;
	std::string field;

	do {
		field = token.getToken(0, '\"', nIndex).trim();

		if (field.equals(ASC2OU("CONSTRAINT"))) {
			nextField = 0;
		} else if (field.equals(ASC2OU("FOREIGN KEY ("))) {
			nextField = 1;
		} else if (field.equals(ASC2OU(") REFERENCES"))) {
			nextField = 2;
		} else if (field.equals(ASC2OU("."))) {
			fields[4] = fields[2];
			nextField = 2;
		} else if (field.equals(ASC2OU("("))) {
			nextField = 3;
		} else if (nextField > -1) {
			fields[nextField] = field;
			nextField = -1;
		}
	} while (nIndex != -1);

	if (token.indexOf(ASC2OU("UPDATE CASCADE"),0) > 0) {
		fields[5] = ASC2OU("UPDATE CASCADE");
	} else if (token.indexOf(ASC2OU("DELETE CASCADE"),0) > 0) {
		fields[5] = ASC2OU("DELETE CASCADE");
	}
#endif
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getImportedKeys() -U- */
sql::ResultSet *
MySQL_ConnectionMetaData::getImportedKeys(const std::string& catalog, const std::string& schema, const std::string& table)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getImportedKeys");
	CPP_INFO_FMT("catalog=%s schema=%s table=%s", catalog.c_str(), schema.c_str(), table.c_str());
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("PKTABLE_CAT");
	rs_field_data.push_back("PKTABLE_SCHEM");
	rs_field_data.push_back("PKTABLE_NAME");
	rs_field_data.push_back("PKCOLUMN_NAME");
	rs_field_data.push_back("FKTABLE_CAT");
	rs_field_data.push_back("FKTABLE_SCHEM");
	rs_field_data.push_back("FKTABLE_NAME");
	rs_field_data.push_back("FKCOLUMN_NAME");
	rs_field_data.push_back("KEY_SEQ");
	rs_field_data.push_back("UPDATE_RULE");
	rs_field_data.push_back("DELETE_RULE");
	rs_field_data.push_back("FK_NAME");
	rs_field_data.push_back("PK_NAME");
	rs_field_data.push_back("DEFERRABILITY");

	char buf[16];
	buf[sizeof(buf) - 1] = '\0';

	if (server_version >= 50116) {
		/* This just doesn't work */
		/* currently this doesn't work - we have to wait for implementation of REFERENTIAL_CONSTRAINTS */
		std::string query("SELECT A.CONSTRAINT_SCHEMA, A.TABLE_NAME, "
									"A.COLUMN_NAME, A.TABLE_SCHEMA, A.TABLE_NAME, "
									"A.COLUMN_NAME, A.ORDINAL_POSITION, NULL AS CONSTRAINT_METHOD, "
									"A.CONSTRAINT_NAME FROM INFORMATION_SCHEMA.KEY_COLUMN_USAGE A, "
									"INFORMATION_SCHEMA.TABLE_CONSTRAINTS B WHERE A.TABLE_SCHEMA='");
									query.append(schema).append(
									"' AND A.CONSTRAINT_NAME=B.CONSTRAINT_NAME AND A.TABLE_NAME='").append(table).append("' "
									"AND B.TABLE_NAME='").append(table).append("' AND A.REFERENCED_TABLE_SCHEMA IS NOT NULL "
									"ORDER BY A.REFERENCED_TABLE_SCHEMA, A.REFERENCED_TABLE_NAME, "
									"A.ORDINAL_POSITION");

		std::auto_ptr<sql::Statement> stmt(connection->createStatement());

		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery(query));

		while (rs->next()) {
			rs_data.push_back("");					// PK_TABLE_CAT
			rs_data.push_back(rs->getString(1));	// PK_TABLE_SCHEMA
			rs_data.push_back(rs->getString(2));	// PK_TABLE_NAME
			rs_data.push_back(rs->getString(3));	// PK_COLUMN_NAME
			rs_data.push_back("");					// FK_TABLE_CAT
			rs_data.push_back(rs->getString(4));	// FK_TABLE_SCHEMA
			rs_data.push_back(rs->getString(5));	// FK_TABLE_NAME
			rs_data.push_back(rs->getString(6));	// FK_COLUMN_NAME
			rs_data.push_back(rs->getString(7));	// KEY_SEQUENCE

			int lFlag = !rs->getString(8).compare("ON UPDATE CASCADE")? importedKeyCascade: importedKeyNoAction;
			rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) lFlag));	// UPDATE_RULE

			lFlag = !rs->getString(8).compare("ON DELETE CASCADE")? importedKeyCascade: importedKeyNoAction;
			rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) lFlag));	// DELETE_RULE

			rs_data.push_back(rs->getString(9));// FK_NAME
			rs_data.push_back("");				// PK_NAME
			rs_data.push_back(my_i_to_a(buf, sizeof(buf)-1, (long) importedKeyNotDeferrable));	// DEFERRABILITY
		}
	} else {
#if 0
		std::string query("SHOW CREATE TABLE `");
		query.append(schema).append("`.`").append(table).append("`");

		std::auto_ptr<sql::Statement> stmt(connection->createStatement());
		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery(query));
		rs->next();
		std::string create_query(rs->getString(2));
#endif
#if 0
		{
			OUString token, statement;
			sal_Int32 nIndex = 0, kSequence = 0;

			do {
				token = statement.getToken(0, '\n', nIndex);
				Sequence< OUString> fields(6);
				if ( parseImportedKeys(token, m_pSettings->quoteIdentifier, fields)) {
					::std::vector< Any > aRow(1);
					aRow.push_back(Any());					// PK_TABLE_CAT
					if (fields[4].getLength()) {
						aRow.push_back(makeAny(fields[4]));	// PK_TABLE_SCHEMA
					} else {
						aRow.push_back(makeAny(schema));	// PK_TABLE_SCHEMA
					}
					aRow.push_back(makeAny(fields[2]));		// PK_TABLE_NAME
					aRow.push_back(makeAny(fields[3]));		// PK_COLUMN_NAME
					aRow.push_back(Any());										// FK_TABLE_CAT
					aRow.push_back(makeAny(schema));			// FK_TABLE_SCHEMA
					aRow.push_back(makeAny(table));			// FK_TABLE_NAME
					aRow.push_back(makeAny(fields[1]));		// FK_COLUMN_NAME

					aRow.push_back(makeAny(
									OUString::valueOf((long) ++kSequence,10)));	// KEY_SEQUENCE

					sal_Int32 lFlag = !(fields[5].equals(ASC2OU("UPDATE CASCADE"))) ?
							com::sun::star::sdbc::KeyRule::NO_ACTION :
							com::sun::star::sdbc::KeyRule::CASCADE;
					aRow.push_back(makeAny(OUString::valueOf(lFlag, 10)));

					lFlag = !((fields[5].equals(ASC2OU("DELETE CASCADE")))) ?
							com::sun::star::sdbc::KeyRule::NO_ACTION :
							com::sun::star::sdbc::KeyRule::CASCADE;
					aRow.push_back(makeAny(OUString::valueOf(lFlag, 10)));

					aRow.push_back(makeAny(fields[0]));		// FK_NAME
					aRow.push_back(makeAny(ASC2OU("PRIMARY")));// PK_NAME
					aRow.push_back(makeAny(
									OUString::valueOf(com::sun::star::sdbc::Deferrability::NONE,10)));	// DEFERRABILITY

					rRows.push_back(aRow);
				}
			} while (nIndex != -1);
		}
#endif
	}
	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getIndexInfo() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getIndexInfo(const std::string& /*catalog*/, const std::string& schema,
										const std::string& table, bool /* unique */, bool /* approximate */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getIndexInfo");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;
	static char buf[5];
	static bool buf_init = false;

	if (!buf_init) {
		snprintf(buf, sizeof(buf), "%d", DatabaseMetaData::tableIndexOther);
	}

	if (server_version > 59999) {
		std::string query("SELECT TABLE_CATALOG, TABLE_SCHEMA, TABLE_NAME, NON_UNIQUE, "
						"INDEX_NAME, SEQ_IN_INDEX, COLUMN_NAME, CARDINALITY "
						"FROM INFORMATION_SCHEMA.STATISTICS WHERE "
						"TABLE_SCHEMA LIKE '");
		query.append(schema).append("' AND TABLE_NAME LIKE '").append(table).
			append("ORDER BY NON_UNIQUE, INDEX_NAME, SEQ_IN_INDEX");

		std::auto_ptr<sql::Statement> stmt(connection->createStatement());

		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery(query));

		while (rs->next()) {
			rs_data.push_back(rs->getString(1));	// Catalog
			rs_data.push_back(rs->getString(2));	// Schema
			rs_data.push_back(rs->getString(3));	// Tablename
			rs_data.push_back(rs->getString(4));	// non unique
			rs_data.push_back("");					// index qualifier
			rs_data.push_back(rs->getString(5));	// index name
			rs_data.push_back(buf);					// index_type
			rs_data.push_back(rs->getString(6));	// ordinal position
			rs_data.push_back(rs->getString(7));	// column name
			rs_data.push_back("ASC");				// asc or desc
			rs_data.push_back(rs->getString(8));	// cardinality
			rs_data.push_back("0");					// pages
			rs_data.push_back("0");					// filter
		}
	} else {
		std::string query("SHOW KEYS FROM `");
		query.append(schema).append("`.`").append(table).append("`");

		std::auto_ptr<sql::Statement> stmt(connection->createStatement());

		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery(query));

		while (rs->next()) {
			rs_data.push_back("");				// Catalog
			rs_data.push_back(schema);			// Schema
			rs_data.push_back(rs->getString(1));// Table_name
			rs_data.push_back(rs->getString(2));// non unique
			rs_data.push_back("");				// index qualifier
			rs_data.push_back(rs->getString(3));// index name
			rs_data.push_back(buf);
			rs_data.push_back(rs->getString(4));// ordinal position
			rs_data.push_back(rs->getString(5));// column name
			rs_data.push_back("ASC");			// asc or desc
			rs_data.push_back(rs->getString(6));// cardinality
			rs_data.push_back("0");				// pages
			rs_data.push_back("");				// filter
		}
	}

	rs_field_data.push_back("TABLE_CAT");
	rs_field_data.push_back("TABLE_SCHEM");
	rs_field_data.push_back("TABLE_NAME");
	rs_field_data.push_back("NON_UNIQUE");
	rs_field_data.push_back("INDEX_QUALIFIER");
	rs_field_data.push_back("INDEX_NAME");
	rs_field_data.push_back("TYPE");
	rs_field_data.push_back("ORDINAL_POSITION");
	rs_field_data.push_back("COLUMN_NAME");
	rs_field_data.push_back("ASC_OR_DESC");
	rs_field_data.push_back("CARDINALITY");
	rs_field_data.push_back("PAGES");
	rs_field_data.push_back("FILTER_CONDITION");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getCDBCMajorVersion() -I- */
int
MySQL_ConnectionMetaData::getCDBCMajorVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getCDBCMajorVersion");
	return 3;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getCDBCMinorVersion() -I- */
int
MySQL_ConnectionMetaData::getCDBCMinorVersion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getCDBCMinorVersion");
	return 0;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxBinaryLiteralLength() -I- */
int
MySQL_ConnectionMetaData::getMaxBinaryLiteralLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxBinaryLiteralLength");
	return 16777208L;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxCatalogNameLength() -I- */
int
MySQL_ConnectionMetaData::getMaxCatalogNameLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxCatalogNameLength");
	return 32;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxCharLiteralLength() -I- */
int
MySQL_ConnectionMetaData::getMaxCharLiteralLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxCharLiteralLength");
	return 16777208;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxColumnNameLength() -I- */
int
MySQL_ConnectionMetaData::getMaxColumnNameLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxColumnNameLength");
	return 64;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxColumnsInGroupBy() -I- */
int
MySQL_ConnectionMetaData::getMaxColumnsInGroupBy()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxColumnsInGroupBy");
	return 64;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxColumnsInIndex() -I- */
int
MySQL_ConnectionMetaData::getMaxColumnsInIndex()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxColumnsInIndex");
	return 16;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxColumnsInOrderBy() -I- */
int
MySQL_ConnectionMetaData::getMaxColumnsInOrderBy()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxColumnsInOrderBy");
	return 64;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxColumnsInSelect() -I- */
int
MySQL_ConnectionMetaData::getMaxColumnsInSelect()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxColumnsInSelect");
	return 256;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxColumnsInTable() -I- */
int
MySQL_ConnectionMetaData::getMaxColumnsInTable()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxColumnsInTable");
	return 512;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxConnections() -I- */
int
MySQL_ConnectionMetaData::getMaxConnections()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxConnections");
	return atoi(connection->getSessionVariable("max_connections").c_str());
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxCursorNameLength() -I- */
int
MySQL_ConnectionMetaData::getMaxCursorNameLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxCursorNameLength");
	return 64;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxIndexLength() -I- */
int
MySQL_ConnectionMetaData::getMaxIndexLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxIndexLength");
	return 256;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxProcedureNameLength() -I- */
int
MySQL_ConnectionMetaData::getMaxProcedureNameLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxProcedureNameLength");
	return 64;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxRowSize() -I- */
int
MySQL_ConnectionMetaData::getMaxRowSize()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxRowSize");
	return 2147483647L - 8; // Max buffer size - HEADER
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxSchemaNameLength() -I- */
int
MySQL_ConnectionMetaData::getMaxSchemaNameLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxSchemaNameLength");
	return 64;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxStatementLength() -I- */
int
MySQL_ConnectionMetaData::getMaxStatementLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxStatementLength");
	return atoi(connection->getSessionVariable("max_allowed_packet").c_str()) - 4;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxStatements() -I- */
int
MySQL_ConnectionMetaData::getMaxStatements()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxStatements");
	return 0;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxTableNameLength() -I- */
int
MySQL_ConnectionMetaData::getMaxTableNameLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxTableNameLength");
	return 64;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxTablesInSelect() -I- */
int
MySQL_ConnectionMetaData::getMaxTablesInSelect()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxTablesInSelect");
	return 256;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getMaxUserNameLength() -I- */
int
MySQL_ConnectionMetaData::getMaxUserNameLength()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getMaxUserNameLength");
	return 16;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getNumericFunctions() -I- */
std::string
MySQL_ConnectionMetaData::getNumericFunctions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getNumericFunctions");
	static const std::string funcs("ABS,ACOS,ASIN,ATAN,ATAN2,BIT_COUNT,CEILING,COS,"
							"COT,DEGREES,EXP,FLOOR,LOG,LOG10,MAX,MIN,MOD,PI,POW,"
							"POWER,RADIANS,RAND,ROUND,SIN,SQRT,TAN,TRUNCATE");
	return funcs;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getPrimaryKeys() -Is- */
sql::ResultSet *
MySQL_ConnectionMetaData::getPrimaryKeys(const std::string& catalog, const std::string& schema, const std::string& table)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getPrimaryKeys");
	CPP_INFO_FMT("catalog=%s schema=%s table=%s", catalog.c_str(), schema.c_str(), table.c_str());
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("TABLE_CAT");
	rs_field_data.push_back("TABLE_SCHEM");
	rs_field_data.push_back("TABLE_NAME");
	rs_field_data.push_back("COLUMN_NAME");
	rs_field_data.push_back("KEY_SEQ");
	rs_field_data.push_back("PK_NAME");

	/* Bind Problems with 49999, check later why */
	if (server_version > 49999) {
#if 0
		static const std::string query("SELECT TABLE_SCHEMA, TABLE_NAME, COLUMN_NAME, "
						"SEQ_IN_INDEX, INDEX_NAME FROM INFORMATION_SCHEMA.STATISTICS "
						"WHERE TABLE_SCHEMA LIKE ? AND TABLE_NAME LIKE ? AND "
						"INDEX_NAME='PRIMARY' ORDER BY TABLE_SCHEMA, TABLE_NAME, INDEX_NAME, SEQ_IN_INDEX");
#endif
		std::string query("SELECT TABLE_SCHEMA, TABLE_NAME, COLUMN_NAME, SEQ_IN_INDEX, INDEX_NAME "
						"FROM INFORMATION_SCHEMA.STATISTICS WHERE TABLE_SCHEMA LIKE '");
		query.append(schema).append("' AND TABLE_NAME LIKE '").append(table).append("'"
					" AND INDEX_NAME='PRIMARY' ORDER BY TABLE_SCHEMA, TABLE_NAME, INDEX_NAME, SEQ_IN_INDEX");

		std::auto_ptr<sql::Statement> stmt(connection->createStatement());

		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery(query));

		while (rs->next()) {
			rs_data.push_back("");					// catalog
			rs_data.push_back(rs->getString(1));	// schema
			rs_data.push_back(rs->getString(2));	// table
			rs_data.push_back(rs->getString(3));	// column
			rs_data.push_back(rs->getString(4));	// sequence number
			rs_data.push_back(rs->getString(5));	// index name
		}
	} else {
		std::string query("SHOW KEYS FROM `");
		query.append(schema).append("`.`").append(table).append("`");

		std::auto_ptr<sql::Statement> stmt(connection->createStatement());
		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery(query));

		while (rs->next()) {
			if (!rs->getString(3).compare("PRIMARY")) {
				rs_data.push_back("");					// catalog
				rs_data.push_back(schema);				// schema
				rs_data.push_back(rs->getString(1));	// table
				rs_data.push_back(rs->getString(5));	// column
				rs_data.push_back(rs->getString(4));	// sequence number
				rs_data.push_back("PRIMARY");			// index name
			}
		}
	}

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getProcedureColumns() -U- */
sql::ResultSet *
MySQL_ConnectionMetaData::getProcedureColumns(const std::string& /* catalog */, const std::string& /*schemaPattern*/,
												const std::string& /*procedureNamePattern*/, const std::string& /*columnNamePattern*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getProcedureColumns");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::getProcedureColumns");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getProcedures() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getProcedures(const std::string& /*catalog*/, const std::string& schemaPattern, const std::string& procedureNamePattern)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getProcedures");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	if (server_version > 49999) {
		std::string query("SELECT ROUTINE_CATALOG, ROUTINE_SCHEMA, ROUTINE_NAME, ROUTINE_COMMENT "
						"FROM INFORMATION_SCHEMA.ROUTINES WHERE ROUTINE_SCHEMA LIKE '");
		query.append(schemaPattern).append("' AND ROUTINE_NAME LIKE '").append(procedureNamePattern.size() ? procedureNamePattern : "%").
			append("' ORDER BY ROUTINE_SCHEMA, ROUTINE_NAME");

		std::auto_ptr<sql::Statement> stmt(connection->createStatement());

		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery(query));
		while (rs->next()) {
			rs_data.push_back(rs->getString(1));	// category
			rs_data.push_back(rs->getString(2));	// schema
			rs_data.push_back(rs->getString(3));	// name
			rs_data.push_back("");					// unsused
			rs_data.push_back("");					// unsused
			rs_data.push_back("");					// unsused
			rs_data.push_back(rs->getString(4));	// remarks
			rs_data.push_back("0");					// type
		}
	}

	rs_field_data.push_back("PROCEDURE_CAT");
	rs_field_data.push_back("PROCEDURE_SCHEM");
	rs_field_data.push_back("PROCEDURE_NAME");
	rs_field_data.push_back("reserved1");
	rs_field_data.push_back("reserved2");
	rs_field_data.push_back("reserved3");
	rs_field_data.push_back("REMARKS");
	rs_field_data.push_back("PROCEDURE_TYPE");
	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getProcedureTerm() -I- */
const std::string&
MySQL_ConnectionMetaData::getProcedureTerm()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getProcedureTerm");
	static const std::string term("procedure");
	return term;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getResultSetHoldability() -I- */
int
MySQL_ConnectionMetaData::getResultSetHoldability()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getResultSetHoldability");
	return sql::ResultSet::HOLD_CURSORS_OVER_COMMIT;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSchemas() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getSchemas()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSchemas");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	std::auto_ptr<sql::Statement> stmt(connection->createStatement());
	std::auto_ptr<sql::ResultSet> rs(
		stmt->executeQuery(server_version > 49999? "SELECT SCHEMA_NAME, CATALOG_NAME FROM INFORMATION_SCHEMA.SCHEMATA ORDER BY SCHEMA_NAME":
												   "SHOW DATABASES"));

	while (rs->next()) {
		rs_data.push_back(rs->getString(1));
		if (server_version > 49999) {
			rs_data.push_back(rs->getString(2));		
		} else {
			rs_data.push_back("");
		}
	}

	rs_field_data.push_back("TABLE_SCHEM");
	rs_field_data.push_back("TABLE_CATALOG");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSchemaTerm() -I- */
const std::string&
MySQL_ConnectionMetaData::getSchemaTerm()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSchemaTerm");
	static const std::string term("database");
	return term;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSearchStringEscape() -I- */
const std::string&
MySQL_ConnectionMetaData::getSearchStringEscape()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSearchStringEscape");
	static const std::string escape("\\");
	return escape;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSQLKeywords() -I- */
const std::string&
MySQL_ConnectionMetaData::getSQLKeywords()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSQLKeywords");
	static const std::string keywords(
				"ACCESSIBLE, ADD, ALL,"\
				"ALTER, ANALYZE, AND, AS, ASC, ASENSITIVE, BEFORE,"\
				"BETWEEN, BIGINT, BINARY, BLOB, BOTH, BY, CALL,"\
				"CASCADE, CASE, CHANGE, CHAR, CHARACTER, CHECK,"\
				"COLLATE, COLUMN, CONDITION, CONNECTION, CONSTRAINT,"\
				"CONTINUE, CONVERT, CREATE, CROSS, CURRENT_DATE,"\
				"CURRENT_TIME, CURRENT_TIMESTAMP, CURRENT_USER, CURSOR,"\
				"DATABASE, DATABASES, DAY_HOUR, DAY_MICROSECOND,"\
				"DAY_MINUTE, DAY_SECOND, DEC, DECIMAL, DECLARE,"\
				"DEFAULT, DELAYED, DELETE, DESC, DESCRIBE,"\
				"DETERMINISTIC, DISTINCT, DISTINCTROW, DIV, DOUBLE,"\
				"DROP, DUAL, EACH, ELSE, ELSEIF, ENCLOSED,"\
				"ESCAPED, EXISTS, EXIT, EXPLAIN, FALSE, FETCH,"\
				"FLOAT, FLOAT4, FLOAT8, FOR, FORCE, FOREIGN, FROM,"\
				"FULLTEXT, GRANT, GROUP, HAVING, HIGH_PRIORITY,"\
				"HOUR_MICROSECOND, HOUR_MINUTE, HOUR_SECOND, IF,"\
				"IGNORE, IN, INDEX, INFILE, INNER, INOUT,"\
				"INSENSITIVE, INSERT, INT, INT1, INT2, INT3, INT4,"\
				"INT8, INTEGER, INTERVAL, INTO, IS, ITERATE, JOIN,"\
				"KEY, KEYS, KILL, LEADING, LEAVE, LEFT, LIKE,"\
				"LOCALTIMESTAMP, LOCK, LONG, LONGBLOB, LONGTEXT,"\
				"LOOP, LOW_PRIORITY, MATCH, MEDIUMBLOB, MEDIUMINT,"\
				"MEDIUMTEXT, MIDDLEINT, MINUTE_MICROSECOND,"\
				"MINUTE_SECOND, MOD, MODIFIES, NATURAL, NOT,"\
				"NO_WRITE_TO_BINLOG, NULL, NUMERIC, ON, OPTIMIZE,"\
				"OPTION, OPTIONALLY, OR, ORDER, OUT, OUTER,"\
				"OUTFILE, PRECISION, PRIMARY, PROCEDURE, PURGE,"\
				"RANGE, READ, READS, READ_ONLY, READ_WRITE, REAL,"\
				"REFERENCES, REGEXP, RELEASE, RENAME, REPEAT,"\
				"REPLACE, REQUIRE, RESTRICT, RETURN, REVOKE, RIGHT,"\
				"RLIKE, SCHEMA, SCHEMAS, SECOND_MICROSECOND, SELECT,"\
				"SENSITIVE, SEPARATOR, SET, SHOW, SMALLINT, SPATIAL,"\
				"SPECIFIC, SQL, SQLEXCEPTION, SQLSTATE, SQLWARNING,"\
				"SQL_BIG_RESULT, SQL_CALC_FOUND_ROWS, SQL_SMALL_RESULT,"\
				"SSL, STARTING, STRAIGHT_JOIN, TABLE, TERMINATED,"\
				"THEN, TINYBLOB, TINYINT, TINYTEXT, TO, TRAILING,"\
				"TRIGGER, TRUE, UNDO, UNION, UNIQUE, UNLOCK,"\
				"UNSIGNED, UPDATE, USAGE, USE, USING, UTC_DATE,"\
				"UTC_TIME, UTC_TIMESTAMP, VALUES, VARBINARY, VARCHAR,"\
				"VARCHARACTER, VARYING, WHEN, WHERE, WHILE, WITH,"\
				"WRITE, X509, XOR, YEAR_MONTH, ZEROFILL");

	return keywords;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSQLStateType() -I- */
int
MySQL_ConnectionMetaData::getSQLStateType()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSQLStateType");
	return sqlStateSQL99;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getStringFunctions() -I- */
const std::string&
MySQL_ConnectionMetaData::getStringFunctions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getStringFunctions");
	static const std::string funcs(
		"ASCII,BIN,BIT_LENGTH,CHAR,CHARACTER_LENGTH,CHAR_LENGTH,CONCAT,"
		"CONCAT_WS,CONV,ELT,EXPORT_SET,FIELD,FIND_IN_SET,HEX,INSERT,"
		"INSTR,LCASE,LEFT,LENGTH,LOAD_FILE,LOCATE,LOCATE,LOWER,LPAD,"
		"LTRIM,MAKE_SET,MATCH,MID,OCT,OCTET_LENGTH,ORD,POSITION,"
		"QUOTE,REPEAT,REPLACE,REVERSE,RIGHT,RPAD,RTRIM,SOUNDEX,"
		"SPACE,STRCMP,SUBSTRING,SUBSTRING,SUBSTRING,SUBSTRING,"
		"SUBSTRING_INDEX,TRIM,UCASE,UPPER");
	return funcs;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSuperTables() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getSuperTables(const std::string& /*catalog*/, const std::string& /*schemaPattern*/, const std::string& /*tableNamePattern*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSuperTables");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("TYPE_CATALOG");
	rs_field_data.push_back("TYPE_SCHEMA");
	rs_field_data.push_back("TYPE_NAME");
	rs_field_data.push_back("SUPERTABLE_NAME");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSuperTypes() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getSuperTypes(const std::string& /*catalog*/, const std::string& /*schemaPattern*/, const std::string& /*typeNamePattern*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSuperTypes");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("TYPE_CATALOG");
	rs_field_data.push_back("TYPE_SCHEMA");
	rs_field_data.push_back("TYPE_NAME");
	rs_field_data.push_back("SUPERTYPE_CATALOG");
	rs_field_data.push_back("SUPERTYPE_SCHEMA");
	rs_field_data.push_back("SUPERTYPE_NAME");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getSystemFunctions() -I- */
const std::string&
MySQL_ConnectionMetaData::getSystemFunctions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getSystemFunctions");
	static const std::string funcs(
			"DATABASE,USER,SYSTEM_USER,"
			"SESSION_USER,PASSWORD,ENCRYPT,LAST_INSERT_ID,VERSION");
	return funcs;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getTablePrivileges() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getTablePrivileges(const std::string& catalog, const std::string& schemaPattern, const std::string& tableNamePattern)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getTablePrivileges");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	std::auto_ptr<sql::Statement> stmt(connection->createStatement());
	std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery("SHOW GRANTS"));

	std::list< std::string > aPrivileges;
	std::list< std::string > aSchemas;
	std::list< std::string > aTables;

	std::string strAllPrivs("ALTER,DELETE,DROP,INDEX,INSERT,LOCK TABLES,SELECT,UPDATE");

	while (rs->next() ) {
		std::string cQuote(getIdentifierQuoteString());
		std::string aGrant = rs->getString(1);
		aGrant = aGrant.replace(0, 6, "");

		size_t pos = aGrant.find("ALL PRIVILEGES");

		if (pos != std::string::npos) {
			aGrant = aGrant.replace(pos, sizeof("ALL PRIVILEGES") - 1, strAllPrivs);
		}

		pos = aGrant.find("ON");

    //ASSERT(pos != std::string::npos);

		aPrivileges.push_back(aGrant.substr(0, pos - 1)); /* -1 for trim */

		aGrant = aGrant.substr(pos + 3); /* remove "ON " */
		pos = 1;
		do {
			pos = aGrant.find(cQuote, pos);
		} while (pos != std::string::npos && aGrant[pos - 1] == '\\');
		/* first char is the quotestring, the last too "`xyz`." Dot is at 5, copy from 1, 5 - 1 - 1 = xyz */

		aSchemas.push_back(aGrant.substr(1, pos - 2)); /* From pos 1, without the quoting */
		int idx = pos + 2;
		pos = idx;
		do {
			pos = aGrant.find(cQuote, pos);
		} while (pos != std::string::npos && aGrant[pos - 1] == '\\');

		/*
		  `aaa`.`xyz`  - jump over the dot and the quote
		  . = 5
		  ` = 6
		  x = 7 = idx
		  ` = 10
		  ` - x = 10 - 7 = 3 -> xyz
		*/
		aTables.push_back(aGrant.substr(idx, idx - pos));
	}
	std::list< std::string > tableTypes;
	tableTypes.push_back(std::string("TABLE"));

	std::auto_ptr<sql::ResultSet> tables(getTables(catalog, schemaPattern, tableNamePattern, tableTypes));
	std::string schema, table;
	while (tables->next()) {
		schema = tables->getString(2);
		table = tables->getString(3);
		std::list<std::string>::iterator it_priv, it_schemas, it_tables;
		it_priv = aPrivileges.begin();
		it_schemas = aSchemas.begin();
		it_tables = aTables.begin();

		for (; it_priv != aPrivileges.end(); ++it_priv, ++it_schemas, ++it_tables) {
			if (it_priv->compare("USAGE") && matchTable(*it_schemas, *it_tables, schema, table)) {
				size_t pos, idx;
				pos = 0;
				do {
					idx = it_priv->find(",", pos);
					std::string privToken = it_priv->substr(pos, idx - pos);
					pos = idx + 1; /* skip ',' */

					if (privToken.find_first_of('/') == std::string::npos) {
						rs_data.push_back(NULL);			// Catalog
						rs_data.push_back(schema);			// Schema
						rs_data.push_back(table);			// Tablename
						rs_data.push_back(NULL);			// Grantor
						rs_data.push_back(getUserName());	// Grantee
						rs_data.push_back(privToken);		// privilege
						rs_data.push_back(NULL);			// is_grantable
					}
				} while (idx != std::string::npos);
				break;
			}
		}
	}

	rs_field_data.push_back("TABLE_CAT");
	rs_field_data.push_back("TABLE_SCHEM");
	rs_field_data.push_back("TABLE_NAME");
	rs_field_data.push_back("GRANTOR");
	rs_field_data.push_back("GRANTEE");
	rs_field_data.push_back("PRIVILEGE");
	rs_field_data.push_back("IS_GRANTABLE");

	return(new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger));
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getTables() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getTables(const std::string& catalog, const std::string& schemaPattern,
									const std::string& tableNamePattern, std::list<std::string> &types)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getTables");
	CPP_INFO_FMT("catalog=%s schemaPattern=%s tablePattern=%s", catalog.c_str(), schemaPattern.c_str(), tableNamePattern.c_str());
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;
	rs_field_data.push_back("TABLE_CAT");
	rs_field_data.push_back("TABLE_SCHEM");
	rs_field_data.push_back("TABLE_NAME");
	rs_field_data.push_back("TABLE_TYPE");
	rs_field_data.push_back("REMARKS");

	/* Bind Problems with 49999, check later why */
	if (server_version > 49999) {
		static const std::string query("SELECT TABLE_CATALOG, TABLE_SCHEMA, TABLE_NAME, "
							"IF(STRCMP(TABLE_TYPE,'BASE TABLE'), TABLE_TYPE, 'TABLE'), "
							"TABLE_COMMENT FROM INFORMATION_SCHEMA.TABLES WHERE "
							"TABLE_SCHEMA  LIKE ? AND TABLE_NAME LIKE ? "
							"ORDER BY TABLE_TYPE, TABLE_SCHEMA, TABLE_NAME");

		std::auto_ptr<sql::PreparedStatement> stmt(connection->prepareStatement(query));
		stmt->setString(1, schemaPattern);
		stmt->setString(2, tableNamePattern);
		
		std::auto_ptr<sql::ResultSet> rs(stmt->executeQuery());

		while (rs->next()) {
			std::list<std::string>::iterator it;
			for (it = types.begin(); it != types.end(); ++it) {
				if (*it == rs->getString(4)) {
					rs_data.push_back(rs->getString(1));
					rs_data.push_back(rs->getString(2));
					rs_data.push_back(rs->getString(3));
					rs_data.push_back(rs->getString(4));
					rs_data.push_back(rs->getString(5));
					break;
				}
			}
		}
	} else {
		std::string query1("SHOW DATABASES LIKE '");
		query1.append(schemaPattern).append("'");

		std::auto_ptr<sql::Statement> stmt1(connection->createStatement());
		std::auto_ptr<sql::ResultSet> rs1(stmt1->executeQuery(query1));
		while (rs1->next()) {
			std::auto_ptr<sql::Statement> stmt2(connection->createStatement());
			std::string current_schema(rs1->getString(1));
			std::string query2("SHOW TABLES FROM `");
			query2.append(current_schema).append("` LIKE '").append(tableNamePattern).append("'");

			std::auto_ptr<sql::ResultSet> rs2(stmt2->executeQuery(query2));

			while (rs2->next()) {
				std::list< std::string >::iterator it;
				for (it = types.begin(); it != types.end(); ++it) {
					/* < 49999 knows only TABLE, no VIEWS */
					/* TODO: Optimize this everytime checking, put it outside of the loop */
					if (!it->compare("TABLE")) {
						CPP_INFO_FMT("[][%s][%s][TABLE][]", current_schema.c_str(), rs2->getString(1).c_str());
						rs_data.push_back("");
						rs_data.push_back(current_schema);
						rs_data.push_back(rs2->getString(1));
						rs_data.push_back("TABLE");
						rs_data.push_back("");
						break;
					}
				}
			}
		}
	}

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getTableTypes() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getTableTypes()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getTableTypes");
	static const char * const table_types[] = {"TABLE", "VIEW", "LOCAL TEMPORARY"};
	static unsigned int requiredVersion[] = {32200, 50000, 32200};

	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("TABLE_TYPE");

	for (int i = 0; i < 3; ++i) {
		if (server_version >= requiredVersion[i]) {
			rs_data.push_back(table_types[i]);
		}
	}
	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getTimeDateFunctions() -I- */
const std::string&
MySQL_ConnectionMetaData::getTimeDateFunctions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getTimeDateFunctions");
	static const std::string funcs(
		"DAYOFWEEK,WEEKDAY,DAYOFMONTH,DAYOFYEAR,MONTH,DAYNAME,"
		"MONTHNAME,QUARTER,WEEK,YEAR,HOUR,MINUTE,SECOND,PERIOD_ADD,"
		"PERIOD_DIFF,TO_DAYS,FROM_DAYS,DATE_FORMAT,TIME_FORMAT,"
		"CURDATE,CURRENT_DATE,CURTIME,CURRENT_TIME,NOW,SYSDATE,"
		"CURRENT_TIMESTAMP,UNIX_TIMESTAMP,FROM_UNIXTIME,"
		"SEC_TO_TIME,TIME_TO_SEC");
	return funcs;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getTypeInfo() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getTypeInfo()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getTypeInfo");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::getTypeInfo");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getUDTs() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getUDTs(const std::string& /*catalog*/, const std::string& /*schemaPattern*/,
									const std::string& /*typeNamePattern*/, std::list<int> & /*types*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getUDTs");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("TYPE_CATALOG");
	rs_field_data.push_back("TYPE_SCHEMA");
	rs_field_data.push_back("TYPE_NAME");
	rs_field_data.push_back("CLASS_NAME");
	rs_field_data.push_back("DATA_TYPE");
	rs_field_data.push_back("REMARKS");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getURL() -U- */
std::string
MySQL_ConnectionMetaData::getURL()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getURL");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::getURL");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getUserName() -I- */
std::string
MySQL_ConnectionMetaData::getUserName()
{
	CPP_ENTER("MySQL_ConnectionMetaData::getUserName");
	std::auto_ptr<sql::Statement> stmt(connection->createStatement());
	std::auto_ptr<sql::ResultSet> rset(stmt->executeQuery("SELECT USER()"));
	if (rset->next()) {
		return std::string(rset->getString(1));
	}
	return NULL;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::getVersionColumns() -I- */
sql::ResultSet *
MySQL_ConnectionMetaData::getVersionColumns(const std::string& /*catalog*/, const std::string& /*schema*/, const std::string& /*table*/)
{
	CPP_ENTER("MySQL_ConnectionMetaData::getVersionColumns");
	std::list<std::string> rs_data;
	std::list<std::string> rs_field_data;

	rs_field_data.push_back("SCOPE");
	rs_field_data.push_back("COLUMN_NAME");
	rs_field_data.push_back("DATA_TYPE");
	rs_field_data.push_back("TYPE_NAME");
	rs_field_data.push_back("COLUMN_SIZE");
	rs_field_data.push_back("BUFFER_LENGTH");
	rs_field_data.push_back("DECIMAL_DIGITS");
	rs_field_data.push_back("PSEUDO_COLUMN");

	return new MySQL_ConstructedResultSet(rs_field_data, rs_data, logger);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::insertsAreDetected() -I- */
bool
MySQL_ConnectionMetaData::insertsAreDetected(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::insertsAreDetected");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::isCatalogAtStart() -I- */
bool
MySQL_ConnectionMetaData::isCatalogAtStart()
{
	CPP_ENTER("MySQL_ConnectionMetaData::isCatalogAtStart");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::isReadOnly() -I- */
bool
MySQL_ConnectionMetaData::isReadOnly()
{
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::locatorsUpdateCopy() -U- */
bool
MySQL_ConnectionMetaData::locatorsUpdateCopy()
{
	CPP_ENTER("MySQL_ConnectionMetaData::locatorsUpdateCopy");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::locatorsUpdateCopy");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::nullPlusNonNullIsNull() -I- */
bool
MySQL_ConnectionMetaData::nullPlusNonNullIsNull()
{
	CPP_ENTER("MySQL_ConnectionMetaData::nullPlusNonNullIsNull");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::nullsAreSortedAtEnd() -I- */
bool
MySQL_ConnectionMetaData::nullsAreSortedAtEnd()
{
	CPP_ENTER("MySQL_ConnectionMetaData::nullsAreSortedAtEnd");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::nullsAreSortedAtStart() -I- */
bool
MySQL_ConnectionMetaData::nullsAreSortedAtStart()
{
	CPP_ENTER("MySQL_ConnectionMetaData::nullsAreSortedAtStart");
	return server_version > 40001 && server_version < 40011;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::nullsAreSortedHigh() -I- */
bool
MySQL_ConnectionMetaData::nullsAreSortedHigh()
{
	CPP_ENTER("MySQL_ConnectionMetaData::nullsAreSortedHigh");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::nullsAreSortedLow() -I- */
bool
MySQL_ConnectionMetaData::nullsAreSortedLow()
{
	CPP_ENTER("MySQL_ConnectionMetaData::nullsAreSortedLow");
	return !nullsAreSortedHigh();
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::othersDeletesAreVisible() -I- */
bool
MySQL_ConnectionMetaData::othersDeletesAreVisible(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::othersDeletesAreVisible");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::othersInsertsAreVisible() -I- */
bool
MySQL_ConnectionMetaData::othersInsertsAreVisible(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::othersInsertsAreVisible");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::othersUpdatesAreVisible() -I- */
bool
MySQL_ConnectionMetaData::othersUpdatesAreVisible(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::othersUpdatesAreVisible");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::ownDeletesAreVisible() -I- */
bool
MySQL_ConnectionMetaData::ownDeletesAreVisible(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::ownDeletesAreVisible");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::ownInsertsAreVisible() -I- */
bool
MySQL_ConnectionMetaData::ownInsertsAreVisible(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::ownInsertsAreVisible");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::ownUpdatesAreVisible() -I- */
bool
MySQL_ConnectionMetaData::ownUpdatesAreVisible(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::ownUpdatesAreVisible");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::storesLowerCaseIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::storesLowerCaseIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::storesLowerCaseIdentifiers");
	return ((lower_case_table_names.compare("1") || lower_case_table_names.compare("2")));
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::storesLowerCaseQuotedIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::storesLowerCaseQuotedIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::storesLowerCaseQuotedIdentifiers");
	return ((lower_case_table_names.compare("1") || lower_case_table_names.compare("2")));
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::storesMixedCaseIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::storesMixedCaseIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::storesMixedCaseIdentifiers");
	return !((lower_case_table_names.compare("1") || lower_case_table_names.compare("2")));
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::storesMixedCaseQuotedIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::storesMixedCaseQuotedIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::storesMixedCaseQuotedIdentifiers");
	return !((lower_case_table_names.compare("1") || lower_case_table_names.compare("2")));
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::storesUpperCaseIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::storesUpperCaseIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::storesUpperCaseIdentifiers");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::storesUpperCaseQuotedIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::storesUpperCaseQuotedIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::storesUpperCaseQuotedIdentifiers");
	return true; // not actually true, but required by JDBC spec!?
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsAlterTableWithAddColumn() -I- */
bool
MySQL_ConnectionMetaData::supportsAlterTableWithAddColumn()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsAlterTableWithAddColumn");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsAlterTableWithDropColumn() -I- */
bool
MySQL_ConnectionMetaData::supportsAlterTableWithDropColumn()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsAlterTableWithDropColumn");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsANSI92EntryLevelSQL -I- */
bool
MySQL_ConnectionMetaData::supportsANSI92EntryLevelSQL()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsANSI92EntryLevelSQL");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsANSI92FullSQL() -I- */
bool
MySQL_ConnectionMetaData::supportsANSI92FullSQL()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsANSI92FullSQL");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsANSI92IntermediateSQL() -I- */
bool
MySQL_ConnectionMetaData::supportsANSI92IntermediateSQL()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsANSI92IntermediateSQL");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsBatchUpdates() -I- */
bool
MySQL_ConnectionMetaData::supportsBatchUpdates()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsBatchUpdates");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsCatalogsInDataManipulation() -I- */
bool
MySQL_ConnectionMetaData::supportsCatalogsInDataManipulation()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsCatalogsInDataManipulation");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsCatalogsInIndexDefinitions() -I- */
bool
MySQL_ConnectionMetaData::supportsCatalogsInIndexDefinitions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsCatalogsInIndexDefinitions");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsCatalogsInPrivilegeDefinitions() -I- */
bool
MySQL_ConnectionMetaData::supportsCatalogsInPrivilegeDefinitions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsCatalogsInPrivilegeDefinitions");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsCatalogsInProcedureCalls() -I- */
bool
MySQL_ConnectionMetaData::supportsCatalogsInProcedureCalls()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsCatalogsInProcedureCalls");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsCatalogsInTableDefinitions() -I- */
bool
MySQL_ConnectionMetaData::supportsCatalogsInTableDefinitions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsCatalogsInTableDefinitions");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsColumnAliasing() -I- */
bool
MySQL_ConnectionMetaData::supportsColumnAliasing()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsColumnAliasing");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsConvert() -I- */
bool
MySQL_ConnectionMetaData::supportsConvert()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsConvert");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsConvert() -U- */
bool
MySQL_ConnectionMetaData::supportsConvert(int /* fromType */, int /* toType */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsConvert");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::supportsConvert");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsCoreSQLGrammar() -I- */
bool
MySQL_ConnectionMetaData::supportsCoreSQLGrammar()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsCoreSQLGrammar");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsCorrelatedSubqueries() -I- */
bool
MySQL_ConnectionMetaData::supportsCorrelatedSubqueries()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsCorrelatedSubqueries");
	return server_version >= 40100;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsDataDefinitionAndDataManipulationTransactions() -I- */
bool
MySQL_ConnectionMetaData::supportsDataDefinitionAndDataManipulationTransactions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsDataDefinitionAndDataManipulationTransactions");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsDataManipulationTransactionsOnly() -I- */
bool
MySQL_ConnectionMetaData::supportsDataManipulationTransactionsOnly()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsDataManipulationTransactionsOnly");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsDifferentTableCorrelationNames() -I- */
bool
MySQL_ConnectionMetaData::supportsDifferentTableCorrelationNames()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsDifferentTableCorrelationNames");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsExpressionsInOrderBy() -I- */
bool
MySQL_ConnectionMetaData::supportsExpressionsInOrderBy()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsExpressionsInOrderBy");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsExtendedSQLGrammar() -I- */
bool
MySQL_ConnectionMetaData::supportsExtendedSQLGrammar()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsExtendedSQLGrammar");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsFullOuterJoins() -I- */
bool
MySQL_ConnectionMetaData::supportsFullOuterJoins()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsFullOuterJoins");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsGetGeneratedKeys() -I- */
bool
MySQL_ConnectionMetaData::supportsGetGeneratedKeys()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsGetGeneratedKeys");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsGroupBy() -I- */
bool
MySQL_ConnectionMetaData::supportsGroupBy()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsGroupBy");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsGroupByBeyondSelect() -I- */
bool
MySQL_ConnectionMetaData::supportsGroupByBeyondSelect()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsGroupByBeyondSelect");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsGroupByUnrelated() -I- */
bool
MySQL_ConnectionMetaData::supportsGroupByUnrelated()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsGroupByUnrelated");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsIntegrityEnhancementFacility() -U- */
bool
MySQL_ConnectionMetaData::supportsIntegrityEnhancementFacility()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsIntegrityEnhancementFacility");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::supportsIntegrityEnhancementFacility");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsLikeEscapeClause() -I- */
bool
MySQL_ConnectionMetaData::supportsLikeEscapeClause()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsLikeEscapeClause");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsLimitedOuterJoins() -I- */
bool
MySQL_ConnectionMetaData::supportsLimitedOuterJoins()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsLimitedOuterJoins");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsMinimumSQLGrammar() -I- */
bool
MySQL_ConnectionMetaData::supportsMinimumSQLGrammar()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsMinimumSQLGrammar");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsMixedCaseIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::supportsMixedCaseIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsMixedCaseIdentifiers");
	return !((lower_case_table_names.compare("1") || lower_case_table_names.compare("2")));
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsMixedCaseQuotedIdentifiers() -I- */
bool
MySQL_ConnectionMetaData::supportsMixedCaseQuotedIdentifiers()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsMixedCaseQuotedIdentifiers");
	return !((lower_case_table_names.compare("1") || lower_case_table_names.compare("2")));
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsMultipleOpenResults() -I- */
bool
MySQL_ConnectionMetaData::supportsMultipleOpenResults()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsMultipleOpenResults");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsMultipleResultSets() -I- */
bool
MySQL_ConnectionMetaData::supportsMultipleResultSets()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsMultipleResultSets");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsMultipleTransactions() -I- */
bool
MySQL_ConnectionMetaData::supportsMultipleTransactions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsMultipleTransactions");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsNamedParameters() -I- */
bool
MySQL_ConnectionMetaData::supportsNamedParameters()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsNamedParameters");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsNonNullableColumns() -I- */
bool
MySQL_ConnectionMetaData::supportsNonNullableColumns()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsNonNullableColumns");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsOpenCursorsAcrossCommit() -I- */
bool
MySQL_ConnectionMetaData::supportsOpenCursorsAcrossCommit()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsOpenCursorsAcrossCommit");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsOpenCursorsAcrossRollback() -I- */
bool
MySQL_ConnectionMetaData::supportsOpenCursorsAcrossRollback()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsOpenCursorsAcrossRollback");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsOpenStatementsAcrossCommit() -I- */
bool
MySQL_ConnectionMetaData::supportsOpenStatementsAcrossCommit()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsOpenStatementsAcrossCommit");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsOpenStatementsAcrossRollback() -I- */
bool
MySQL_ConnectionMetaData::supportsOpenStatementsAcrossRollback()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsOpenStatementsAcrossRollback");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsOrderByUnrelated() -I- */
bool
MySQL_ConnectionMetaData::supportsOrderByUnrelated()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsOrderByUnrelated");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsOuterJoins() -I- */
bool
MySQL_ConnectionMetaData::supportsOuterJoins()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsOuterJoins");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsPositionedDelete() -I- */
bool
MySQL_ConnectionMetaData::supportsPositionedDelete()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsPositionedDelete");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsPositionedUpdate() -I- */
bool
MySQL_ConnectionMetaData::supportsPositionedUpdate()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsPositionedUpdate");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsResultSetConcurrency() -U- */
bool
MySQL_ConnectionMetaData::supportsResultSetConcurrency(int /* type */, int /* concurrency */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsResultSetConcurrency");
	throw sql::MethodNotImplementedException("MySQL_ConnectionMetaData::supportsResultSetConcurrency");
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsResultSetHoldability() -I- */
bool
MySQL_ConnectionMetaData::supportsResultSetHoldability(int holdability)
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsResultSetHoldability");
	return (holdability == sql::ResultSet::HOLD_CURSORS_OVER_COMMIT);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsResultSetType() -I- */
bool
MySQL_ConnectionMetaData::supportsResultSetType(int type)
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsResultSetType");
	return (type == sql::ResultSet::TYPE_SCROLL_INSENSITIVE);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSavepoints() -I- */
bool
MySQL_ConnectionMetaData::supportsSavepoints()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSavepoints");
	return (server_version >= 40014 || server_version >= 40101);
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSchemasInDataManipulation() -I- */
bool
MySQL_ConnectionMetaData::supportsSchemasInDataManipulation()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSchemasInDataManipulation");
	return server_version >= 32200;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSchemasInIndexDefinitions() -I- */
bool
MySQL_ConnectionMetaData::supportsSchemasInIndexDefinitions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSchemasInIndexDefinitions");
	return server_version >= 32200;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSchemasInPrivilegeDefinitions() -I- */
bool
MySQL_ConnectionMetaData::supportsSchemasInPrivilegeDefinitions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSchemasInPrivilegeDefinitions");
	return server_version > 32200;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSchemasInProcedureCalls() -I- */
bool
MySQL_ConnectionMetaData::supportsSchemasInProcedureCalls()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSchemasInProcedureCalls");
	return server_version >= 32200;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSchemasInTableDefinitions() -I- */
bool
MySQL_ConnectionMetaData::supportsSchemasInTableDefinitions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSchemasInTableDefinitions");
	return server_version >= 32200;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSelectForUpdate() -I- */
bool
MySQL_ConnectionMetaData::supportsSelectForUpdate()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSelectForUpdate");
	return server_version >= 40000;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsStatementPooling() -I- */
bool
MySQL_ConnectionMetaData::supportsStatementPooling()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsStatementPooling");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsStoredProcedures() -I- */
bool
MySQL_ConnectionMetaData::supportsStoredProcedures()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsStoredProcedures");
	return server_version >= 50000;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSubqueriesInComparisons() -I- */
bool
MySQL_ConnectionMetaData::supportsSubqueriesInComparisons()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSubqueriesInComparisons");
	return server_version >= 40100;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSubqueriesInExists() -I- */
bool
MySQL_ConnectionMetaData::supportsSubqueriesInExists()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSubqueriesInExists");
	return server_version >= 40100;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSubqueriesInIns() -I- */
bool
MySQL_ConnectionMetaData::supportsSubqueriesInIns()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSubqueriesInIns");
	return server_version >= 40100;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsSubqueriesInQuantifieds() -I- */
bool
MySQL_ConnectionMetaData::supportsSubqueriesInQuantifieds()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsSubqueriesInQuantifieds");
	return server_version >= 40100;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsTableCorrelationNames() -I- */
bool
MySQL_ConnectionMetaData::supportsTableCorrelationNames()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsTableCorrelationNames");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsTransactionIsolationLevel() -I- */
bool
MySQL_ConnectionMetaData::supportsTransactionIsolationLevel(int /* level */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsTransactionIsolationLevel");
	return server_version >= 32336;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsTransactions() -I- */
bool
MySQL_ConnectionMetaData::supportsTransactions()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsTransactions");
	return server_version >= 32315;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsTypeConversion() -I- */
bool
MySQL_ConnectionMetaData::supportsTypeConversion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsTypeConversion");
	return true;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsUnion() -I- */
bool
MySQL_ConnectionMetaData::supportsUnion()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsUnion");
	return server_version >= 40000;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::supportsUnionAll() -I- */
bool
MySQL_ConnectionMetaData::supportsUnionAll()
{
	CPP_ENTER("MySQL_ConnectionMetaData::supportsUnionAll");
	return server_version >= 40000;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::updatesAreDetected() -I- */
bool
MySQL_ConnectionMetaData::updatesAreDetected(int /* type */)
{
	CPP_ENTER("MySQL_ConnectionMetaData::updatesAreDetected");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::usesLocalFilePerTable() -I- */
bool
MySQL_ConnectionMetaData::usesLocalFilePerTable()
{
	CPP_ENTER("MySQL_ConnectionMetaData::usesLocalFilePerTable");
	return false;
}
/* }}} */


/* {{{ MySQL_ConnectionMetaData::usesLocalFiles() -I- */
bool
MySQL_ConnectionMetaData::usesLocalFiles()
{
	CPP_ENTER("MySQL_ConnectionMetaData::usesLocalFiles");
	return false;
}
/* }}} */

/* {{{ MySQL_ConnectionMetaData::matchTable() -I- */
bool
MySQL_ConnectionMetaData::matchTable(std::string &sPattern, std::string & tPattern, std::string & schema, std::string & table)
{
	CPP_ENTER("MySQL_ConnectionMetaData::matchTable");
	return (!sPattern.compare(schema) || !sPattern.compare("*")) && (!tPattern.compare(table)  || !tPattern.compare("*"));
}


};/* namespace mysql */
};/* namespace sql */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
