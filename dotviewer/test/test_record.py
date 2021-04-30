import py
from dotviewer.drawgraph import TextSnippetRecordLR, record_to_nested_lists
from dotviewer.conftest import option

def test_split_record():
    s = "a|{b|c|d|e}|{f|{g|h}|{i|j}|k|l}"
    l = record_to_nested_lists(s)
    assert l == ['a', ['b', 'c', 'd', 'e'], ['f', ['g', 'h'], ['i', 'j'], 'k', 'l']]
    s = "{An Mrecord|has rounded|corners}"
    l = record_to_nested_lists(s)
    s = "a|b|c"
    l = record_to_nested_lists(s)
    assert l == s.split("|")

def test_ignore_angular():
    s = "a|{<portname>b|c|d|e}|{f|{g|h}|{i|j}|k|l}"
    l = record_to_nested_lists(s)
    assert l == ['a', ['b', 'c', 'd', 'e'], ['f', ['g', 'h'], ['i', 'j'], 'k', 'l']]

def test_show():
    if not option.pygame:
        py.test.skip("--pygame not enabled")
    from dotviewer.drawgraph import GraphLayout
    layout = GraphLayout(1, 2.0972, 0.97222)
    layout.add_node('rec', 1.0486, 0.48611, 2.0972, 0.97222, "{a|b|c}|d|e|f|{{g|h}|i}", 'solid', 'record', 'black', 'lightgrey')
    layout.display()
