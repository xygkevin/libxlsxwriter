/*
 * Tests for the libxlsxwriter library.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 * Copyright 2014-2025, John McNamara, jmcnamara@cpan.org.
 *
 */

#include "../ctest.h"
#include "../helper.h"

#include "../../../include/xlsxwriter/worksheet.h"
#include "../../../include/xlsxwriter/shared_strings.h"

// Test assembling a complete Worksheet file.
CTEST(worksheet, worksheet_condtional_format02) {

    char* got;
    char exp[] =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
            "<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">"
              "<dimension ref=\"A1:B4\"/>"
              "<sheetViews>"
                "<sheetView tabSelected=\"1\" workbookViewId=\"0\"/>"
              "</sheetViews>"
              "<sheetFormatPr defaultRowHeight=\"15\"/>"
              "<sheetData>"
                "<row r=\"1\" spans=\"1:2\">"
                  "<c r=\"A1\">"
                    "<v>10</v>"
                  "</c>"
                  "<c r=\"B1\">"
                    "<v>5</v>"
                  "</c>"
                "</row>"
                "<row r=\"2\" spans=\"1:2\">"
                  "<c r=\"A2\">"
                    "<v>20</v>"
                  "</c>"
                "</row>"
                "<row r=\"3\" spans=\"1:2\">"
                  "<c r=\"A3\">"
                    "<v>30</v>"
                  "</c>"
                "</row>"
                "<row r=\"4\" spans=\"1:2\">"
                  "<c r=\"A4\">"
                    "<v>40</v>"
                  "</c>"
                "</row>"
              "</sheetData>"
              "<conditionalFormatting sqref=\"A1\">"
                "<cfRule type=\"cellIs\" priority=\"1\" operator=\"greaterThan\">"
                  "<formula>$B$1</formula>"
                "</cfRule>"
              "</conditionalFormatting>"
              "<pageMargins left=\"0.7\" right=\"0.7\" top=\"0.75\" bottom=\"0.75\" header=\"0.3\" footer=\"0.3\"/>"
            "</worksheet>";

    FILE* testfile = lxw_tmpfile(NULL);

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;
    worksheet_select(worksheet);

    worksheet_write_number(worksheet, CELL("A1"), 10, NULL);
    worksheet_write_number(worksheet, CELL("A2"), 20, NULL);
    worksheet_write_number(worksheet, CELL("A3"), 30, NULL);
    worksheet_write_number(worksheet, CELL("A4"), 40, NULL);

    worksheet_write_number(worksheet, CELL("B1"), 5, NULL);

    lxw_conditional_format *conditional_format = calloc(1, sizeof(lxw_conditional_format));

    conditional_format->type         = LXW_CONDITIONAL_TYPE_CELL;
    conditional_format->criteria     = LXW_CONDITIONAL_CRITERIA_GREATER_THAN;
    conditional_format->value_string = "$B$1";
    conditional_format->format       = NULL;
    worksheet_conditional_format_cell(worksheet, CELL("A1"), conditional_format);

    free(conditional_format);

    lxw_worksheet_assemble_xml_file(worksheet);

    RUN_XLSX_STREQ_SHORT(exp, got);

    lxw_worksheet_free(worksheet);
}

// This version uses a range formula "$B$1" -> "=$B$1".
CTEST(worksheet, worksheet_condtional_format02b) {

    char* got;
    char exp[] =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n"
            "<worksheet xmlns=\"http://schemas.openxmlformats.org/spreadsheetml/2006/main\" xmlns:r=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships\">"
              "<dimension ref=\"A1:B4\"/>"
              "<sheetViews>"
                "<sheetView tabSelected=\"1\" workbookViewId=\"0\"/>"
              "</sheetViews>"
              "<sheetFormatPr defaultRowHeight=\"15\"/>"
              "<sheetData>"
                "<row r=\"1\" spans=\"1:2\">"
                  "<c r=\"A1\">"
                    "<v>10</v>"
                  "</c>"
                  "<c r=\"B1\">"
                    "<v>5</v>"
                  "</c>"
                "</row>"
                "<row r=\"2\" spans=\"1:2\">"
                  "<c r=\"A2\">"
                    "<v>20</v>"
                  "</c>"
                "</row>"
                "<row r=\"3\" spans=\"1:2\">"
                  "<c r=\"A3\">"
                    "<v>30</v>"
                  "</c>"
                "</row>"
                "<row r=\"4\" spans=\"1:2\">"
                  "<c r=\"A4\">"
                    "<v>40</v>"
                  "</c>"
                "</row>"
              "</sheetData>"
              "<conditionalFormatting sqref=\"A1\">"
                "<cfRule type=\"cellIs\" priority=\"1\" operator=\"greaterThan\">"
                  "<formula>$B$1</formula>"
                "</cfRule>"
              "</conditionalFormatting>"
              "<pageMargins left=\"0.7\" right=\"0.7\" top=\"0.75\" bottom=\"0.75\" header=\"0.3\" footer=\"0.3\"/>"
            "</worksheet>";

    FILE* testfile = lxw_tmpfile(NULL);

    lxw_worksheet *worksheet = lxw_worksheet_new(NULL);
    worksheet->file = testfile;
    worksheet_select(worksheet);

    worksheet_write_number(worksheet, CELL("A1"), 10, NULL);
    worksheet_write_number(worksheet, CELL("A2"), 20, NULL);
    worksheet_write_number(worksheet, CELL("A3"), 30, NULL);
    worksheet_write_number(worksheet, CELL("A4"), 40, NULL);

    worksheet_write_number(worksheet, CELL("B1"), 5, NULL);

    lxw_conditional_format *conditional_format = calloc(1, sizeof(lxw_conditional_format));

    conditional_format->type         = LXW_CONDITIONAL_TYPE_CELL;
    conditional_format->criteria     = LXW_CONDITIONAL_CRITERIA_GREATER_THAN;
    conditional_format->value_string = "=$B$1";
    conditional_format->format       = NULL;
    worksheet_conditional_format_cell(worksheet, CELL("A1"), conditional_format);

    free(conditional_format);

    lxw_worksheet_assemble_xml_file(worksheet);

    RUN_XLSX_STREQ_SHORT(exp, got);

    lxw_worksheet_free(worksheet);
}

