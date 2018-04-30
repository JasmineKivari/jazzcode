package ca.camosun.androidtemperatureconverter;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    private static String na = "N/A";

    private interface Lambda {
        double convert(Double input);
    }

    private class Conversion {
        private String name;
        private String leftLabel;
        private String rightLabel;
        private Lambda leftConversion;
        private Lambda rightConversion;

        private Conversion(String name, String leftLabel, String rightLabel, Lambda leftConversion, Lambda rightConversion) {
            this.name = name;
            this.leftLabel = leftLabel;
            this.rightLabel = rightLabel;
            this.leftConversion = leftConversion;
            this.rightConversion = rightConversion;
        }
    }

    private ArrayList<Conversion> conversions;
    private Lambda leftConversion;
    private Lambda rightConversion;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        conversions = new ArrayList<>();
        conversions.add(new Conversion("Area","ac > ha",
        "ha > ac", (a) -> a * 0.404686, (h) -> h * 2.47105));
        conversions.add(new Conversion("Length", "ft > m",
        "m > ft", (f) -> f * 0.3048, (m) -> m * 3.28084));
        conversions.add(new Conversion("Temperature","F > C",
        "C > F", (f) -> (f - 32.0) * 5.0 / 9.0, (c) -> c * 9.0 / 5 + 32));
        conversions.add(new Conversion("Weight", "lbs > kg",
        "kg > lbs", (l) -> l * 0.453592, (k) -> k * 2.20462));

        // Creating spinner values
        ArrayList<String> spinnerValues = new ArrayList<>();
        for (Conversion conversion : conversions) {
            spinnerValues.add(conversion.name);
        }
        ArrayAdapter<String> adapter = new ArrayAdapter<>(
        this, android.R.layout.simple_spinner_item, spinnerValues);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        Spinner spinner = findViewById(R.id.spinner);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(this);

        // Initial button labels
        Button leftButton = findViewById(R.id.leftButton);
        leftButton.setText(conversions.get(0).leftLabel);
        Button rightButton = findViewById(R.id.rightButton);
        rightButton.setText(conversions.get(0).rightLabel);
    }

    public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {
        Button leftButton = findViewById(R.id.leftButton);
        leftButton.setText(conversions.get(pos).leftLabel);
        Button rightButton = findViewById(R.id.rightButton);
        rightButton.setText(conversions.get(pos).rightLabel);
        leftConversion = conversions.get(pos).leftConversion;
        rightConversion = conversions.get(pos).rightConversion;

    }

    public void onNothingSelected(AdapterView<?> parent) {
        // Nothing selected by spinner
        Button leftButton = findViewById(R.id.leftButton);
        leftButton.setText(na);
        Button rightButton = findViewById(R.id.rightButton);
        rightButton.setText(na);
        leftConversion = null;
        rightConversion = null;

    }

    public void leftButton(View view) {
        // Do the left button conversion
        EditText converterField = findViewById(R.id.converterField);
        String fieldString = converterField.getText().toString();
        try {
            if (leftConversion != null) {
                converterField.setText(String.valueOf(leftConversion.convert(Double.parseDouble(fieldString))));
            }
        }
        catch (Exception e) {
            // Conversion failed
            converterField.setText(na);
        }
    }

    public void rightButton(View view) {
        // Do the right conversion
        EditText converterField = findViewById(R.id.converterField);
        String fieldString = converterField.getText().toString();
        try {
            if (rightConversion != null) {
                converterField.setText(String.valueOf(rightConversion.convert(Double.parseDouble(fieldString))));
            }
        }
        catch (Exception e) {
            // Conversion failed
            converterField.setText(na);
        }
    }
}
