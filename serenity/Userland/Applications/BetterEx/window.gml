@W::BWidget{
    fill_with_background_color: true
    layout: @GUI::VerticalBoxLayout {
        margins: [8]
        spacing: 4
    }
    @GUI::TextBox{
        name: "name"
        text: "name"
    }
    @GUI::Label{
        name: "id"
        text: "no id yet"
    }

    @GUI::Widget {
        layout: @GUI::HorizontalBoxLayout {
            spacing: 8
        }
        @GUI::Button{
            name: "open"
            text: "open"
        }
        @GUI::Button{
            name: "close"
            text: "close"
        }
        @GUI::Button{
            name: "wait"
            text: "wait"
        }
        @GUI::Button{
            name: "signal"
            text: "signal"
        }
    }
}