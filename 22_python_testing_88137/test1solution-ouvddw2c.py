import pytest
import ssolution.py

def test_File_dialog():
    assert var is None
    
def test_Load_excel_data():
    assert var is None
    
def test_clear_data():
    assert var is None
    
def test_weeklyPaid(hours_worked, wage):
    if hours_worked > 40:
        return 40 * wage + (hours_worked - 40) * wage * 1.5
    else:
        return hours_worked * wage
    