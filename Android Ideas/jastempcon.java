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

    private static String nA = "n/a";
    private ArrayList<ConvertAll> convertAlls;
    private Lambda rightConverter;
    private Lambda leftConverter;


    private class ConvertAll {
        private String labelName;
        private String lLabel;
        private String rLabel;
        private Lambda leftConverter;
        private Lambda rightConverter;


        private ConvertAll(String labelName, String lLabel, String rLabel, Lambda leftConverter, Lambda rightConverter) {

            this.labelName = labelName;
            this.lLabel = lLabel;
            this.rLabel = rLabel;
            this.leftConverter = leftConverter;
            this.rightConverter = rightConverter;

        }
    }

    public interface Lambda {
        double convert(Double input);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        convertAlls = new ArrayList<>();
        convertAlls.add(new ConvertAll("Area", "Ac to Ha", "Ha to AC", (ac) -> ac * 0.404686, (ha) -> ha * 2.47105));
        convertAlls.add(new ConvertAll("Length", "Ft to M", "M to FT", (ft) -> ft * 0.3048, (m) -> m * 3.28084));
        convertAlls.add(new ConvertAll("Temperature", "F to C", "C to F", (fa) -> (fa - 32.0) * 5.0 / 9.0, (cel) -> cel * 9.0 / 5 + 32));
        convertAlls.add(new ConvertAll("Weight", "Lbs to Kg", "Kg to Lbs", (lbs) -> lbs * 0.453592, (ki) -> ki * 2.20462));

        //TextView converterLabel = (TextView) findViewById(R.id.converterLabel3);
        //converterLabel.setText(tempLabel);
        //Button leftButton = (Button) findViewById(R.id.leftButton);
        //leftButton.setText(c2fLabel);
        //Button rightButton = (Button) findViewById(R.id.rightButton);
        //rightButton.setText(f2cLabel);
        ArrayList<String> spinnerValues = new ArrayList<>();
        for (ConvertAll conversion : convertAlls) {
            spinnerValues.add(conversion.labelName);
        }
        ArrayAdapter<String> adapter;
        adapter = new ArrayAdapter<>(
        this, android.R.layout.simple_spinner_dropdown_item, spinnerValues);
        Spinner spinner = findViewById(R.id.spinner);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(this);

        Button leftButton = findViewById(R.id.leftButton);
        leftButton.setText(convertAlls.get(0).lLabel);

        Button rightButton = findViewById(R.id.rightButton);
        rightButton.setText(convertAlls.get(0).rLabel);

    }

    public void leftButton(View view) {
        EditText converterField = findViewById(R.id.converterField);
        String slField;
        slField = converterField.getText().toString();
        try {
            if (leftConverter != null) {

                converterField.setText(String.valueOf(leftConverter.convert(Double.parseDouble(slField))));
            }
        } catch (Exception e) {
            converterField.setText(nA);
        }
    }

    public void rightButton(View view) {
        EditText converterField;
        converterField = (EditText) findViewById(R.id.converterField);
        String srField = converterField.getText().toString();
        try {
            if (rightConverter != null) {

                converterField.setText(String.valueOf(rightConverter.convert(Double.parseDouble(srField))));

            }
        } catch (Exception e) {
            converterField.setText(nA);
        }
    }

    public void onNothingSelected(AdapterView<?> parent) {
        Button leftButton = findViewById(R.id.leftButton);
        leftButton.setText(nA);

        Button rightButton = findViewById(R.id.rightButton);
        rightButton.setText(nA);

        leftConverter = null;
        rightConverter = null;
    }

    public void onItemSelected(AdapterView<?> parent, View view, int pos, long id) {

        Button leftButton = findViewById(R.id.leftButton);
        leftButton.setText(convertAlls.get(pos).lLabel);

        Button rightButton = findViewById(R.id.rightButton);
        rightButton.setText(convertAlls.get(pos).rLabel);

        leftConverter = convertAlls.get(pos).leftConverter;
        rightConverter = convertAlls.get(pos).rightConverter;

    }


}





