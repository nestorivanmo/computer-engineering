import pandas as pd
import plotly.graph_objects as go
from plotly.subplots import make_subplots

def plot_pcl_vs_no_pcl(y):
    labels = ["Sin PCL", "PCL"]
    df = pd.DataFrame({'label': y})
    values = df["label"].value_counts().to_numpy()

    TEMPLATE='plotly_white'

    BLUE_COLOR = "#37689e"
    TURQUOISE_COLOR = "#4bb4c8"
    LIGHT_BLUE_COLOR = "#9bbdcf"
    YELLOW_COLOR = "#e49a21"
    LIGHT_YELLOW_COLOR = "#f2c576"
    RED_COLOR = "#da2f20"
    LIGHT_RED_COLOR = "#e66f4b"

    binary_colors = [LIGHT_BLUE_COLOR, LIGHT_RED_COLOR]

    fig = make_subplots(rows=1, cols=2, specs=[[{'type':'domain'}, {'type':'xy'}]])
    fig.add_trace(go.Pie(
        labels=labels,
        values=values,
        marker_colors = binary_colors, hole=0.4, 
        textfont_color='white', textfont_size=20
    ), 1, 1)

    fig.add_trace(go.Bar(
        x=labels,
        y=values, marker_color=binary_colors,
        text =values, textfont_color='white', textfont_size=15
    ), 1, 2)

    fig.update_layout(
        title = dict(text="PCL vs. Sin PCL", font_size=25),
        showlegend=False, template=TEMPLATE, width=1000
    )
    fig.show()