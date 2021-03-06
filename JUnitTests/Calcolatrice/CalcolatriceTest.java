import static org.junit.jupiter.api.Assertions.assertEquals;
import org.junit.jupiter.params.ParameterizedTest;
import org.junit.jupiter.params.provider.CsvFileSource;

class CalcolatriceTest {

	@ParameterizedTest
	@CsvFileSource(resources = "./divisione_test.csv")
	public void test_divisione(int a, int b, double oracle, double delta){
		Calcolatrice CalcolatriceTest = new Calcolatrice(/*constructor arguments*/);
		assertEquals(oracle,CalcolatriceTest.divisione(a, b),delta, "divisione FAILED");
	}
}