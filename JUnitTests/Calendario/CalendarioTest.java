import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;

class CalendarioTest {

	@ParameterizedTest
	@CsvFileSource(resources = "./calend_test.csv")
	public void test_calend(int d, int m, int a, Object oracle){
		Calendario CalendarioTest = new Calendario();
		assertEquals(String.valueOf(oracle), String.valueOf(CalendarioTest.calend(d, m, a)),"calend FAILED");
	}
}